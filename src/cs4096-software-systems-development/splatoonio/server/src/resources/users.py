
import falcon
import json

from src.resources.helpers import read_req_body, expect_fields

class Users(object):
    def __init__(self):
        # TODO: We should use database for state
        self.users = {}

    def on_get(self, req, resp):
        resp_dict = {
            #TODO: We should use constants for these special protocol strings
            'users': list(self.users.keys())
        }

        resp.body = json.dumps(resp_dict)

    @read_req_body
    @expect_fields('name') # TODO: We should use constants
    def on_post(self, req, resp, data, name):
        if name not in self.users:
            self.users[name] = None
        else:
            resp.status = falcon.HTTP_400

