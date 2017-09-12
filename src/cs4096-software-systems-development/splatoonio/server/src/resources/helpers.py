
import json

def read_req_body(func):

    def wrapper(self, req, resp):
        data = json.loads(req.stream.read().decode('utf8'))
        return func(self, req, resp, data)

    return wrapper

def expect_fields(*fields):
    def decorator(func):

        def wrapper(self, req, resp, data):
            args = []
            for field in fields:
                if field in data:
                    args.append(data[field])
                else:
                    raise NotImplementedError()

            return func(self, req, resp, data, *args)

        return wrapper
    return decorator

def expect_data_fields(*fields):
    def decorator(func):

        @read_req_body
        @expect_fiels(*fields)
        def wrapper(self, req, resp, data, *args):
            return func(self, req, resp, *args)

        return wrapper
    return decorator

