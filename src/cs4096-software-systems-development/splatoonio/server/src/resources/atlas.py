
import falcon
import json

from src.api import Api
from src.resources.helpers import return_json, expect_fields

class Atlas(object):
    def __init__(self):
        self.maps = {}
        # TODO: Replace with database
        self.maps[0] = Map(GeoPlane(
            GeoCoord(37.955185, -91.775621),
            GeoCoord(37.946861, -91.767553),
            GeoCoord(37.946861, -91.775621),
            GeoCoord(37.955185, -91.767553),
        ))

    @return_json
    def on_get(self, req, resp):
        return self.maps[0].to_json()

class Map(object):
    # TODO: use constants to determine width/length (or pull from database)
    def __init__(self, plane, invalid=None):
        self.plane = plane
        if invalid is None:
            invalid = []

        self.invalid = invalid

    @property
    def width(self):
        return 100

    @property
    def length(self):
        return 250

    def to_json(self):
        return {
            Api.plane: self.plane.to_json(),
            Api.width: self.width,
            Api.length: self.length,
            Api.invalid: self.invalid
        }

class GeoPlane(object):
    def __init__(self, top_left, top_right, bot_left, bot_right):
        self.top_left = top_left
        self.top_right = top_right
        self.bot_left = bot_left
        self.bot_right = bot_right

    def to_json(self):
        return list(map(lambda el: el.to_json(), [
            self.top_left, self.top_right, self.bot_right, self.bot_left
        ]))

class GeoCoord(object):
    def __init__(self, lat, lng):
        self.lat = lat
        self.lng = lng

    def to_json(self):
        return {
            Api.latitude: self.lat,
            Api.longitude: self.lng
        }

