// 15-745 S18 Assignment 1: FunctionInfo.cpp
// Group:
////////////////////////////////////////////////////////////////////////////////

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/Support/raw_ostream.h"

#include <iostream>

using namespace llvm;

namespace {
  class FunctionInfo : public FunctionPass {
  public:
    static char ID;
    FunctionInfo() : FunctionPass(ID) { }
    ~FunctionInfo() { }

    // We don't modify the program, so we preserve all analyses
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }

    // Do some initialization
    bool doInitialization(Module &M) override {
      outs() << "Name,\tArgs,\tCalls,\tBlocks,\tInsns\n";
      return false;
    }

    // Print output for each function
    bool runOnFunction(Function &F) override {
      int countArguments =  F.arg_end() - F.arg_begin();
      auto numberOfCalls = 0;
      int numberOfBb = 0;
      int numberOfInstr = 0;
      for(auto bb_iter = F.begin();bb_iter != F.end(); bb_iter++){
        numberOfBb++;
        CallInst *call_inst = dyn_cast<CallInst>(bb_iter);
        if(call_inst != nullptr){
          numberOfCalls++;
        }
        for(auto instr_iter = bb_iter->begin();instr_iter != bb_iter->end();instr_iter++){
          numberOfInstr++;
        }
      }
      outs() << F.getName() << "\t" << countArguments << "\t" << numberOfCalls << "\t" << numberOfBb << "\t" << numberOfInstr << "\n";
      return false;
    }
  };
}

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char FunctionInfo::ID = 0;
static RegisterPass<FunctionInfo> X("function-info", "15745: Function Information", false, false);