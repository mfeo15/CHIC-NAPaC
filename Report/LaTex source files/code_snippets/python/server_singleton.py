@classmethod
def get_instance(cls):
    if not cls.__instance:
        cls.__instance = Server()
        
    return cls.__instance