import os
import re
from flask import Flask, jsonify, render_template, request

from cs50 import SQL
from helpers import lookup

# Configure application
app = Flask(__name__)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///mashup.db")


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Render map"""
    if not os.environ.get("API_KEY"):
        raise RuntimeError("API_KEY not set")
    return render_template("index.html", key=os.environ.get("API_KEY"))


@app.route("/articles")
def articles():
    """Look up articles for geo"""
    geo = request.args.get("geo")

    # Ensure parameters are present
    if not geo:
        raise RuntimeError("missing geo")

    # Return a dictionary containing article titles and URL {"link": item["link"], "title": item["title"]}
    article_list = lookup(geo)
    return jsonify(article_list)


@app.route("/search")
def search():
    """Search for places that match query"""
    q = request.args.get("q")

    # if postal code entered
    if q.isdigit() is True:
        # if valid format
        if len(q) is 5:
            result = db.execute("SELECT * FROM places WHERE postal_code = :q", q=q)
        # if less than 5 digits entered
        else:
            q += "%"
            result = db.execute("SELECT * FROM places WHERE postal_code LIKE :q", q=q)
    # if string entered
    else:
        # convert to list and get rid of any commas
        q = q.replace(",", "").split(" ")

        # if state included
        if len(q[-1]) is 2:
            state = q[-1] + "%"
            city = " ".join(q[:len(q) - 1]) + "%"
            result = db.execute(
                "SELECT * FROM places WHERE place_name LIKE :city AND admin_code1 LIKE :state", city=city, state=state)
        # if no state entered
        else:
            city = " ".join(q[:len(q)]) + "%"
            result = db.execute("SELECT * FROM places WHERE place_name LIKE :city", city=city)

    return jsonify(result)


@app.route("/update")
def update():
    """Find up to 10 places within view"""

    # Ensure parameters are present
    if not request.args.get("sw"):
        raise RuntimeError("missing sw")
    if not request.args.get("ne"):
        raise RuntimeError("missing ne")

    # Ensure parameters are in lat,lng format
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
        raise RuntimeError("invalid sw")
    if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
        raise RuntimeError("invalid ne")

    # Explode southwest corner into two variables
    sw_lat, sw_lng = map(float, request.args.get("sw").split(","))

    # Explode northeast corner into two variables
    ne_lat, ne_lng = map(float, request.args.get("ne").split(","))

    # Find 10 cities within view, pseudorandomly chosen if more within view
    if sw_lng <= ne_lng:

        # Doesn't cross the antimeridian
        rows = db.execute("""SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude AND longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM()
                          LIMIT 10""",
                          sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    else:

        # Crosses the antimeridian
        rows = db.execute("""SELECT * FROM places
                          WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude OR longitude <= :ne_lng)
                          GROUP BY country_code, place_name, admin_code1
                          ORDER BY RANDOM()
                          LIMIT 10""",
                          sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    # Output places as JSON
    return jsonify(rows)
