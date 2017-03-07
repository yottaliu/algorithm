#!/usr/bin/env bash
echo `grep '^#define sort' test.c | awk '{print $3}'`.c
