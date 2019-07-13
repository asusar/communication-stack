/*
 * Copyright (c) 2018-2019 Faculty of Engineering Ain Shams University Dr.Sherif Hammad Email: Sherif.hammad@eng.asu.edu.eg Eng.Mohamed abdelhay Email: mhmd.a.elhay@gmail.com.
 *
 * This file is part of ASUSAR
 * (see https://github.com/asusar/communication-stack).
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include "include/Std_Types.h"
#include "include/Com_Types.h"
#include "include/Com_helper.h"
#include "include/Com_Cfg.h"

boolean validateSignalID (Com_SignalIdType SignalId)
{
	if(SignalId<COM_NUM_OF_SIGNAL)
		return TRUE;
	return FALSE;
}


uint64 power(uint8 x,uint8 y)
{
	uint64 result = x;

	if (y == 0)
		return 1;

	for (; y>1 ; y--)
	{
		result = result * x;
	}
	return result;
}


boolean compare_float(uint64 f1, uint64 f2)
{
 float precision = 0.0001;
 if (((f1 - precision) < f2) &&
     ((f1 + precision) > f2))
  {
   return TRUE;
  }
 else if ((f1-precision)>f2 && (f1+precision)>f2){
     return TRUE;
 }
 else
  {
   return FALSE;
  }
}
