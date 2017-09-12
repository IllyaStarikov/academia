
import falcon
 
from src.routes import add_routes

api = falcon.API()
add_routes(api)

