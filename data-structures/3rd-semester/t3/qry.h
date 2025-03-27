#include "libraries.h"
#include "energy.h"
#include "List.h"
#include "d.h"
#include "lr.h"
#include "mc.h"
#include "mv.h"
#include "paths.h"
#include "svg.h"
#include "SRbTree.h"

#ifndef QRY_H
#define QRY_H

FILE* newReport(AllPaths paths);
void endReport(FILE* txt);

void readQry(FILE* pTxt, SRbTree tree, AllPaths paths);

#endif