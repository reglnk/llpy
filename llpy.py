import llpy_util
from copy import deepcopy

swap = llpy_util.swap

class Reference:
    def __init__(self, obj):
        self.ref = obj
    
    @property
    def value(self):
        return self.ref
    
    @value.setter
    def value(self, obj):
        objcopy = deepcopy(obj)
        llpy_util.swap(self.ref, objcopy)
        # then content of previous self.ref is destroyed
        
        # @todo more low-level 'magic':
        # 1. just garbage-collect content of self.ref
        # 2. then shallow copy newval there
        # 3. increment refcount of newval content

def ref(obj):
    return Reference(obj)
