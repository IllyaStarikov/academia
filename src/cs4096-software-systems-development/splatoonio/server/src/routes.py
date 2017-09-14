
from src.resources.users import Users

def add_routes(app):
    add_app_route(app, '/users', Users())

def add_app_route(app, uri, handler):
    app.add_route('/api' + uri, handler)

