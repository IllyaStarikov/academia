
import falcon
import json

from src.api import Api
from src.resources.helpers import return_json, expect_fields

class Users(object):
    def __init__(self):
        self.users = {}

    @return_json
    def on_get(self, req, resp):
        return {
           Api.user_list: list(self.users.keys())
        }

    @expect_fields(Api.username)
    def on_post(self, req, resp, username):
        if username not in self.users:
            self.users[username] = None
        else:
            resp.status = falcon.HTTP_409

    @expect_fields(Api.username)
    def on_delete(self, req, resp, username):
        del self.users[username]

