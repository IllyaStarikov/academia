
from src.resources.users import Users

def add_routes(api):
    add_api_route(api, '/users', Users())

def add_api_route(api, uri, handler):
    api.add_route('/api' + uri, handler)

