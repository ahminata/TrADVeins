#!/usr/bin/env python
# Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
# Copyright (C) 2008-2019 German Aerospace Center (DLR) and others.
# This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v2.0
# which accompanies this distribution, and is available at
# http://www.eclipse.org/legal/epl-v20.html
# SPDX-License-Identifier: EPL-2.0

# @file    copyfiles_sumocfg.py
# @author  Ahmed
# @date    2007-10-25
# @version $Id$

from __future__ import absolute_import
from __future__ import print_function


import os
from subprocess import call
seeds=range(9)
v_densitys=[20,40,60,80,100,150,200,250,300,350,400,450,500]
#seeds=range(0)
#v_densitys=[20]

for seed in seeds:
    for v_density in v_densitys:
        call(['cp','manhattan.sumocfg','data/manhattan'+str(v_density)+ '_' + str(seed)+'/manhattan.sumocfg'])
        call(['cp','osm.launchd.xml','data/manhattan'+str(v_density)+ '_' + str(seed)+'/osm.launchd.xml'])
        call(['cp','poly.xml','data/manhattan'+str(v_density)+ '_' + str(seed)+'/poly.xml'])
