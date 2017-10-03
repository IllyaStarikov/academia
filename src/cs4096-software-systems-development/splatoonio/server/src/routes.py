
from src.resources.users import Users
from src.resources.atlas import Atlas

def add_routes(app):
    add_app_route(app, '/users', Users())
    add_app_route(app, '/atlas/{map_id}', Atlas())

def add_app_route(app, uri, handler):
    app.add_route('/api' + uri, handler)

