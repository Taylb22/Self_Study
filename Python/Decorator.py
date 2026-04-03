import time

def meu_decorador(func):
    def wrapper():
        func()
    return wrapper

@meu_decorador
def hello_world():
    print("Hello World")
    
hello_world()
