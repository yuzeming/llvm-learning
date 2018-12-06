#include <map>

#include "printCode/printCode.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;
using namespace std;

static RegisterPass<printCode> X(
	"printCode",
	"print IR instructions",
	false, false);


char printCode::ID = 0;

void printCode::getAnalysisUsage(AnalysisUsage &AU) const {
}

printCode::printCode() : FunctionPass(ID) {}

bool printCode::runOnFunction(Function & F) 
{
	static int numBBID = 1;
	static int numInstID = 1;	
	
	map<Instruction *, int> mapInstToID;
	map<BasicBlock *, int> mapBBToID;

	for(Function::iterator BB = F.begin(); BB != F.end(); BB ++)
	{
		BasicBlock * pBB = &*BB;
		mapBBToID[pBB] = numBBID++; 
		for(BasicBlock::iterator II = BB->begin(); II != BB->end(); II ++ )
		{
			Instruction * pI = &* II;
			mapInstToID[pI] = numInstID++;
		}
	}
	
	errs() << "\nFUNCTION " << F.getName() << "\n";

	for(Function::iterator BB = F.begin(); BB != F.end(); BB ++ )
	{
		errs() << "\nBASIC BLOCK " << mapBBToID[&*BB] << "\n";
		
		for(BasicBlock::iterator II = BB->begin(); II != BB->end(); II ++)
		{
			Instruction * pI = &* II;
			errs() << "%" << mapInstToID[pI] << ":\t";
			errs() << pI->getOpcodeName() << "\t";
			
			for(unsigned i = 0 ; i < pI->getNumOperands(); i ++ )
			{
				Value * itValue = pI->getOperand(i);

				if(Instruction * pOPI = dyn_cast<Instruction>(itValue))
				{
					errs() << "%" << mapInstToID[pOPI] << " ";
				}
				else if(itValue->hasName())
				{
					errs() << itValue->getName() << " ";
				}
				else
				{
					errs() << "XXX ";
				}
			}			

			errs() << "\n";
		} 
	}


	return false;
}
