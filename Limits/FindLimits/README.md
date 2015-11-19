To use the find_limits_13tev script, a yields.txt file must be present in the FindLimits directory. 

The mass spectrum parameters can be edited for different ranges of mass points. mass_0 is the lowest mass used, mass_Increment is the increment between mass points, and mass_spec is the number of mass points. 

The script is executed with cmsRun. It will create individual datacards for every mass of every decay channel (et, mt, tt, and em for now), run combine Asymptotic, and create output files containing the limits as well as root output from running combine. 

Then, the combineCards.py script is called to combine the 4 channels cards for each mass point. Combine is again run for each mass and the limits text file and output root files for combined channels are created.    