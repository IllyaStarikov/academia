# Serializer: functions to serialize and unserialize json communication strings
from joueur.base_game_object import BaseGameObject

def is_game_object_reference(d):
    return (isinstance(d, dict) and len(d) == 1 and 'id' in d)

def is_object(obj):
    return (isinstance(obj, dict) or isinstance(obj, list)) or isinstance(obj, BaseGameObject)

def serialize(data):
    if not isinstance(data, (list, dict, BaseGameObject)):
        return data

    if isinstance(data, BaseGameObject):
        return {'id': data.id}

    serialized = {}
    for key in data:
        value = data[key]
        if is_object(value):
            serialized[key] = serialize(value)
        else:
            serialized[key] = value
    return serialized

def deserialize(data, game):
    if not isinstance(data, (list, dict, BaseGameObject)):
        return data

    if is_game_object_reference(data):
        return game.get_game_object(data['id'])

    # else if we got here it's a list or dict
    deserialized = [None] * len(data) if isinstance(data, list) else {}
    seq_iter = data.items if isinstance(data, dict) else enumerate(data)
    for key, value in seq_iter:
        if is_object(value):
            deserialized[key] = deserialize(value, game)
        else:
            deserialized[key] = value

    return deserialized
