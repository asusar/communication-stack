
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

#ifndef STD_TYPES_H_
#define STD_TYPES_H_



/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

/* Boolean Data Type */
typedef unsigned char			boolean;
typedef unsigned char         	uint8;          /*           0 .. 255             */
typedef unsigned short        	uint16;         /*           0 .. 65535           */
typedef unsigned long         	uint32;         /*           0 .. 4294967295      */
typedef signed char           	sint8;          /*        -128 .. +127            */
typedef signed short          	sint16;         /*      -32768 .. +32767          */
typedef signed long           	sint32;         /* -2147483648 .. +2147483647     */
typedef signed long long      	sint64;
typedef unsigned long long    	uint64;         /*       0..18446744073709551615  */
typedef float                 	float32;
typedef double                	float64;

#define	NULL 0

//uint8[n]



typedef enum
{
    E_OK,
    E_NOT_OK,
}Std_ReturnType;


#endif /* STD_TYPES_H_ */

