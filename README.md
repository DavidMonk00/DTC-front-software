# DTC-front-software
Sofware simulation code for the the stub formatting firware block. This goes before the router in the DTC card, which forms part of the trigger pathway for the CMS experiment at CERN.

## Status
- Code is standalone from CMSSW, there is no interface between the two at this time. Stubs are read in through a text file of containing a set of 64x64b words.
- Output is again proprietarty to the code at this time, stub parameters can be outputted in human readable format using the `print()` method
