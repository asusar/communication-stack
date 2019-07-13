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
#pragma CHECK_MISRA("none")
#include <stdint.h>


//Function to delay t microseconds
/*
void Delay_Us(long t){
	  long i , j;
	   i = 0;
	   j = 0;
	  while(i<t){
       while(j<3){
				 j++;
			 //Do Nothing
			 }
			 i++;
	  }
}
//Function to delay t milliseconds
void Delay_ms(long t){
	  long i , j;
	   i = 0;
	   j = 0;
	  while(i<t){
       while(j<3180){
				 j++;
			 //Do Nothing
			 }
			 i++;
	  }
}
*/void Delay_Us(int32_t t){
      int32_t i , j;
       i = 0;
       j = 0;
      while(i<t){
       while(j<3){
                 j++;
             //Do Nothing
             }
             i++;
      }
}
//Function to delay t milliseconds
void Delay_ms(int32_t t){
      int32_t i , j;
       i = 0;
       j = 0;
      while(i<t){
       while(j<3180){
                 j++;
             //Do Nothing
             }
             i++;
      }
}
