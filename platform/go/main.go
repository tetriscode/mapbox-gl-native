package main

/*
#cgo LDFLAGS: -L/usr/local/Cellar/boost/1.66.0/lib
#include <stdlib.h>
#include "mb.h"
*/
import "C"
import "log"

func main() {
	log.Print(C.doit())
	log.Print(C.doit())
	log.Print(C.doit())
	log.Print(C.doit())
	log.Print(C.doit())
	log.Print(C.doit())
}
