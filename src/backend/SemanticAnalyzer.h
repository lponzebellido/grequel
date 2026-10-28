#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "../frontend/AST.h"
#include "SymbolTable.h"
#include <string>
#include <unordered_map>

class SemanticAnalyzer : public ASTVisitor {
private:
  SymbolTable &symbolTable;
  bool hasError;
  bool annotationLoaded;
  bool sequenceLoaded;
  int controlFlowDepth;
  std::unordered_map<std::string, std::string> constantValues;

  void reportError(const std::string &message);
  double parseValue(const std::string &val);
  std::string resolveConstant(const std::string &value) const;
  bool validateConstantReference(const std::string &value);
  bool parseGenomicDistance(const std::string &value,
                            const std::string &unit,
                            const std::string &label, bool requireUnit,
                            long double &basePairs,
                            bool pluralWholeNumbers = false);

public:
  SemanticAnalyzer(SymbolTable &symTab);

  void analyze(ProgramNode *node);
  bool hadError() const { return hasError; }

  void visit(SimpleConditionNode *node) override;
  void visit(BinaryConditionNode *node) override;
  void visit(NotConditionNode *node) override;
  void visit(LoadStmtNode *node) override;
  void visit(UseStmtNode *node) override;
  void visit(ExportStmtNode *node) override;
  void visit(LetStmtNode *node) override;
  void visit(DefinePromotersStmtNode *node) override;
  void visit(DefineModuleStmtNode *node) override;
  void visit(FindOptNode *node) override;
  void visit(FindStmtNode *node) override;
  void visit(ExtractStmtNode *node) override;
  void visit(SetOpStmtNode *node) override;
  void visit(CountStmtNode *node) override;
  void visit(ScanStmtNode *node) override;
  void visit(AnalyzeStmtNode *node) override;
  void visit(ValidateStmtNode *node) override;
  void visit(GroupStmtNode *node) override;
  void visit(TranslateStmtNode *node) override;
  void visit(IfStmtNode *node) override;
  void visit(ForeachStmtNode *node) override;
  void visit(ProgramNode *node) override;
};

#endif
