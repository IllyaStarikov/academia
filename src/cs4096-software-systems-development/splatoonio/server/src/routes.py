
from src.resources.users import Users

def add_routes(api):
    api.add_route('/users', Users())

