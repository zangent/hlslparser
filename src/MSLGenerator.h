#ifndef MSL_GENERATOR_H
#define MSL_GENERATOR_H

#include "CodeWriter.h"
#include "HLSLTree.h"

struct Parameter_Table;

namespace M4
{

class  HLSLTree;
struct HLSLFunction;
struct HLSLStruct;
    
/**
 * This class is used to generate MSL shaders.
 */
class MSLGenerator
{

public:

    enum Target
    {
        Target_VertexShader,
        Target_FragmentShader,
    };
    
    enum Flags
    {
        Flags_ConstShadowSampler = 0x1
    };

    MSLGenerator();
    
    bool Generate(HLSLTree* tree, Target target, const char* entryName, int flags = 0);
    const char* GetResult() const;

private:
    
    // @@ Rename class argument. Add buffers & textures.
    struct ClassArgument
    {
        const char* name;
        HLSLType type;
        //const char* typeName;     // @@ Do we need more than the type name?
        const char* registerName;

        ClassArgument * nextArg;
        
        ClassArgument(const char* name, HLSLType type, const char * registerName) :
            name(name), type(type), registerName(registerName)
		{
			nextArg = NULL;
		}
    };

    void AddClassArgument(ClassArgument * arg);

    void Prepass(HLSLTree* tree, Target target, HLSLFunction* entryFunction);
    void CleanPrepass();
    
    void OutputStatements(int indent, HLSLStatement* statement);
    void OutputAttributes(int indent, HLSLAttribute* attribute);
    void OutputDeclaration(HLSLDeclaration* declaration);
    void OutputStruct(int indent, HLSLStruct* structure);
    void OutputBuffer(int indent, HLSLBuffer* buffer);
    void OutputFunction(int indent, HLSLFunction* function);
    void OutputExpression(HLSLExpression* expression, HLSLExpression* parentExpression);
    void OutputCast(const HLSLType& type);
    
    void OutputArguments(HLSLArgument* argument);
    void OutputDeclaration(const HLSLType& type, const char* name, HLSLExpression* assignment, bool isRef = false, bool isConst = false, int alignment = 0);
    void OutputDeclarationType(const HLSLType& type, bool isConst = false, bool isRef = false, int alignment = 0);
    void OutputDeclarationBody(const HLSLType& type, const char* name, HLSLExpression* assignment, bool isRef = false);
    void OutputExpressionList(HLSLExpression* expression);
    void OutputFunctionCallStatement(int indent, HLSLFunctionCall* functionCall);
    void OutputFunctionCall(HLSLFunctionCall* functionCall);

    int ParseRegister(const char* registerName, int& nextRegister);
    
    void Error(const char* format, ...);

private:

    CodeWriter      m_writer;

    HLSLTree*       m_tree;
    const char*     m_entryName;
    Target          m_target;
    
    bool            m_error;

    ClassArgument * m_firstClassArgument;
    ClassArgument * m_lastClassArgument;
};

} // M4

#endif
