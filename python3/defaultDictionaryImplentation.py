'''
A simple implentation of collections.defaultdictionary.
A simple implentation of recursive dictionary.
'''
__author__ = "Hanzhou Tang"
__email__  = "hanzhoutang@gmail.com"
class defaultDict:
    def __init__(self,f):
        self.factory = f
        self.d = dict()
        
    def __getitem__(self,key):
        if key in self.d:
            return self.d[key]
        else:
            self.d[key] = self.factory()
            return self.d[key] 
        
    def __setitem__(self,k,v):
        self.d[k] = v 
        
    def __str__(self):
        return str(self.d)
    
    def __repr__(self):
        return repr(self.d)
    


T = lambda : defaultDict(T) 
tree = T()
tree['c']['x'] = 'hj'
tree['a']['b']['c'] = 1234567 
print(tree) 
