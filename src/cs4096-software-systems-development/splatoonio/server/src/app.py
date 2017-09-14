
import falcon
 
from src.routes import add_routes

app = falcon.API()
add_routes(app)

