
#include "llvm/Pass.h"

using namespace llvm;
using namespace std;

struct printCode: public FunctionPass {
	static char ID;
	printCode();
	virtual void getAnalysisUsage(AnalysisUsage &AU) const;
	virtual bool runOnFunction(Function &F);	

};
