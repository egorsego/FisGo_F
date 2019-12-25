/*
 * config.h
 */

#ifndef SRC_APPL_INCLUDE_CONFIG_H_
#define SRC_APPL_INCLUDE_CONFIG_H_

#include <string.h>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include "log.h"
#include "convert.h"
#include "agents.h"
#include "tax.h"
#include "dynamic_mask.h"

#define YEAR_CONSTANT       1900
#define YEAR_MINIMUM        2018
#define YEAR_MAXIMUM        2020

static const int CONFIG_VERSION = 14;

static const string fisgo_cur_version = "1.27.0";
static const string kkt_reg_version   = "001";
static const string VERSION_FOR_STAT  =  "100.6.1.3";
static const string TIMESTAMP_FILE    = "timestamp";

const string modelName   =        "Dreamkas_F";
const string upModelName =        "DREAMKAS_F";
const string product     = "dreamkasFRedirect";

#pragma once