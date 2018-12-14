#!/usr/bin/env python
''' show usage of __getattribute__ '''
__author__ = "Hanzhou Tang"
__email__  = "hanzhoutang@gmail.com"
import types
class Demo:
    def f(self, value):
        return value + 1
    
    def __init__(self,funcs):
        self.funcs = funcs
    
    def __getattribute__(self,name):
        v = super().__getattribute__(name)
        if name == "__dict__":
            return v
        funcs = self.__dict__["funcs"]
        if name in funcs:
            f = funcs[name]
            f_new = f(self,v.__func__)
            return types.MethodType(f_new,self)
        return v
       
def f_wrapper(self,f):
    '''f_wrapper is an existing decorator'''
    def f_ret(this,*arg):
        ret = f(self,*arg)
        return ret * 2
    return f_ret

class subclassDemo(Demo):
    def f(self,value):
        return -value

class subsubclassDemo(subclassDemo):
    def f(self,value):
        return value * 2
    
if __name__ == "__main__":
    demo = Demo({"f":f_wrapper})
    child = subclassDemo({"f":f_wrapper})
    childOfChild = subsubclassDemo({"f":f_wrapper})
    print(demo.f(3))
    print("call from subclassDemo")
    print(child.f(3))
    print("call from subsubclassDemo")
    print(childOfChild.f(3))  
    
