
import falcon
import json

def read_req_data(func):

    def wrapper(self, req, resp):
        data = json.loads(req.stream.read().decode('utf8'))
        return func(self, req, resp, data)

    return wrapper

def expect_data_fields(*fields):
    def decorator(func):

        def wrapper(self, req, resp, data):
            args = []
            for field in fields:
                if field in data:
                    args.append(data[field])
                else:
                    resp.status = falcon.HTTP_400
                    return

            return func(self, req, resp, data, *args)

        return wrapper
    return decorator

def expect_fields(*fields):
    def decorator(func):

        @read_req_data
        @expect_data_fields(*fields)
        def wrapper(self, req, resp, data, *args):
            return func(self, req, resp, *args)

        return wrapper
    return decorator

def return_json(func):

    def wrapper(self, req, resp):
        resp.body = json.dumps(func(self, req, resp))

    return wrapper

