#Tue Jul 19 13:30:17 2016"""Automatically generated. DO NOT EDIT please"""
from GaudiKernel.Proxy.Configurable import *

class TMiniNtuple( ConfigurableAlgorithm ) :
  __slots__ = { 
    'OutputLevel' : 0, # int
    'Enable' : True, # bool
    'ErrorMax' : 1, # int
    'ErrorCount' : 0, # int
    'AuditAlgorithms' : False, # bool
    'AuditInitialize' : False, # bool
    'AuditReinitialize' : False, # bool
    'AuditRestart' : False, # bool
    'AuditExecute' : False, # bool
    'AuditFinalize' : False, # bool
    'AuditBeginRun' : False, # bool
    'AuditEndRun' : False, # bool
    'AuditStart' : False, # bool
    'AuditStop' : False, # bool
    'MonitorService' : 'MonitorSvc', # str
    'RegisterForContextService' : False, # bool
    'OutputFileName' : 'output.root', # str
    'InputFileName' : [  ], # list
    'Debug' : True, # bool
    'ApplyLeptonSkim' : False, # bool
    'MinLeptonPt' : 9000.0000, # float
  }
  _propertyDocDct = { 
    'RegisterForContextService' : """ The flag to enforce the registration for Algorithm Context Service """,
  }
  def __init__(self, name = Configurable.DefaultName, **kwargs):
      super(TMiniNtuple, self).__init__(name)
      for n,v in kwargs.items():
         setattr(self, n, v)
  def getDlls( self ):
      return 'MiniNtuple'
  def getType( self ):
      return 'TMiniNtuple'
  pass # class TMiniNtuple
