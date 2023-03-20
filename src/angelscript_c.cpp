//
// Created by Firmament on 19/03/2023.
//

#include "../vendor/sdk/angelscript/include/angelscript.h"

extern "C" {
	// region Interface declarations - engine
	// Memory management
	int asEngine_AddRef( asIScriptEngine* engine ) {
		return engine->AddRef();
	}
	int asEngine_Release( asIScriptEngine* engine ) {
		return engine->Release();
	}
	int asEngine_ShutdownAndRelease( asIScriptEngine* engine ) {
		return engine->ShutDownAndRelease();
	}

	// Engine properties
	int asEngine_SetEngineProperty( asIScriptEngine* engine, asEEngineProp property, asPWORD value ) {
		return engine->SetEngineProperty( property, value );
	}
	asPWORD asEngine_GetEngineProperty( asIScriptEngine* engine, asEEngineProp property ) {
		return engine->GetEngineProperty( property );
	}

	// Compiler messages
	int asEngine_SetMessageCallback( asIScriptEngine* engine, asFUNCTION_t& callback, void* obj, asDWORD callConv ) {
		return engine->SetMessageCallback( asFUNCTION( callback ), obj, callConv );
	}
	int asEngine_ClearMessageCallback( asIScriptEngine* engine ) {
		return engine->ClearMessageCallback(  );
	}
	int asEngine_WriteMessage( asIScriptEngine* engine, char* section, int row, int col, asEMsgType type, char* message ) {
		return engine->WriteMessage(  );
	}

	// JIT Compiler
	int asEngine_SetJITCompiler( asIScriptEngine* engine, asIJITCompiler* compiler ) {
		return engine->SetJITCompiler(  );
	}
	asIJITCompiler* asEngine_GetJITCompiler( asIScriptEngine* engine ) {
		return engine->piler(  );
	}

	// Global functions
	int asEngine_RegisterGlobalFunction( asIScriptEngine* engine, char* declaration, asFUNCTION_t& funcPointer, asDWORD callConv, void* auxiliary ) {
		return engine->RegisterGlobalFunction(  );
	}
	asUINT asEngine_GetGlobalFunctionCount( asIScriptEngine* engine ) {
		return engine->GetGlobalFunctionCount(  );
	}
	asIScriptFunction* asEngine_GetGlobalFunctionByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->Function(  );
	}
	asIScriptFunction* asEngine_GetGlobalFunctionByDecl( asIScriptEngine* engine, char* declaration ) {
		return engine->Function(  );
	}

	// Global properties
	int asEngine_RegisterGlobalProperty( asIScriptEngine* engine, const char* declaration, void* pointer ) {
		return engine->RegisterGlobalProperty(  );
	}
	asUINT asEngine_GetGlobalPropertyCount( asIScriptEngine* engine ) {
		return engine->GetGlobalPropertyCount(  );
	}
	int asEngine_GetGlobalPropertyByIndex( asIScriptEngine* engine, asUINT index, const char** name, const char** nameSpace, int* typeId, bool* isConst, const char** configGroup, void** pointer, asDWORD* accessMask ) {
		return engine->GetGlobalPropertyByIndex(  );
	}
	int asEngine_GetGlobalPropertyIndexByName( asIScriptEngine* engine, const char* name ) {
		return engine->GetGlobalPropertyIndexByName(  );
	}
	int asEngine_GetGlobalPropertyIndexByDecl( asIScriptEngine* engine, const char* decl ) {
		return engine->GetGlobalPropertyIndexByDecl(  );
	}

	// Object types
	int asEngine_RegisterObjectType( asIScriptEngine* engine, const char* obj, int byteSize, asDWORD flags ) {
		return engine->RegisterObjectType(  );
	}
	int asEngine_RegisterObjectProperty( asIScriptEngine* engine, const char* obj, const char* declaration, int byteOffset, int compositeOffset, bool isCompositeIndirect ) {
		return engine->RegisterObjectProperty(  );
	}
	int asEngine_RegisterObjectMethod( asIScriptEngine* engine, const char* obj, const char* declaration, const asFUNCTION_t& funcPointer, asDWORD callConv, void* auxiliary, int compositeOffset, bool isCompositeIndirect ) {
		return engine->RegisterObjectMethod(  );
	}
	int asEngine_RegisterObjectBehaviour( asIScriptEngine* engine, const char* obj, asEBehaviours behaviour, const char* declaration, const asFUNCTION_t& funcPointer, asDWORD callConv, void* auxiliary, int compositeOffset, bool isCompositeIndirect ) {
		return engine->RegisterObjectBehaviour(  );
	}
	int asEngine_RegisterInterface( asIScriptEngine* engine, const char* name ) {
		return engine->RegisterInterface(  );
	}
	int asEngine_RegisterInterfaceMethod( asIScriptEngine* engine, const char* intf, const char* declaration ) {
		return engine->RegisterInterfaceMethod(  );
	}
	asUINT asEngine_GetObjectTypeCount( asIScriptEngine* engine ) {
		return engine->GetObjectTypeCount(  );
	}
	asITypeInfo* asEngine_GetObjectTypeByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->e_GetObjectTypeByIndex(  );
	}

	// String factory
	int asEngine_RegisterStringFactory( asIScriptEngine* engine, const char* datatype, asIStringFactory* factory ) {
		return engine->RegisterStringFactory(  );
	}
	int asEngine_GetStringFactoryReturnTypeId( asIScriptEngine* engine, asDWORD* flags ) {
		return engine->GetStringFactoryReturnTypeId(  );
	}

	// Default array type
	int asEngine_RegisterDefaultArrayType( asIScriptEngine* engine, const char* type ) {
		return engine->RegisterDefaultArrayType(  );
	}
	int asEngine_GetDefaultArrayTypeId( asIScriptEngine* engine ) {
		return engine->GetDefaultArrayTypeId(  );
	}

	// Enums
	int asEngine_RegisterEnum( asIScriptEngine* engine, const char* type ) {
		return engine->RegisterEnum(  );
	}
	int asEngine_RegisterEnumValue( asIScriptEngine* engine, const char* type, const char* name, int value ) {
		return engine->RegisterEnumValue(  );
	}
	asUINT asEngine_GetEnumCount( asIScriptEngine* engine ) {
		return engine->GetEnumCount(  );
	}
	asITypeInfo* asEngine_GetEnumByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->e_GetEnumByIndex(  );
	}

	// Funcdefs
	int asEngine_RegisterFuncdef( asIScriptEngine* engine, const char* decl ) {
		return engine->RegisterFuncdef(  );
	}
	asUINT asEngine_GetFuncdefCount( asIScriptEngine* engine ) {
		return engine->GetFuncdefCount(  );
	}
	asITypeInfo* asEngine_GetFuncdefByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->e_GetFuncdefByIndex(  );
	}

	// Typedefs
	int asEngine_RegisterTypedef( asIScriptEngine* engine, const char* type, const char* decl ) {
		return engine->RegisterTypedef(  );
	}
	asUINT asEngine_GetTypedefCount( asIScriptEngine* engine ) {
		return engine->GetTypedefCount(  );
	}
	asITypeInfo* asEngine_GetTypedefByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->e_GetTypedefByIndex(  );
	}

	// Configuration groups
	int asEngine_BeginConfigGroup( asIScriptEngine* engine, const char* groupName ) {
		return engine->BeginConfigGroup(  );
	}
	int asEngine_EndConfigGroup( asIScriptEngine* engine ) {
		return engine->EndConfigGroup(  );
	}
	int asEngine_RemoveConfigGroup( asIScriptEngine* engine, const char* groupName ) {
		return engine->RemoveConfigGroup(  );
	}
	asDWORD asEngine_SetDefaultAccessMask( asIScriptEngine* engine, asDWORD defaultMask ) {
		return engine->SetDefaultAccessMask(  );
	}
	int asEngine_SetDefaultNamespace( asIScriptEngine* engine, const char* nameSpace ) {
		return engine->SetDefaultNamespace(  );
	}
	const char* asEngine_GetDefaultNamespace( asIScriptEngine* engine ) {
		return engine->GetDefaultNamespace(  );
	}

	// Script modules
	asIScriptModule*
	asEngine_GetModule( asIScriptEngine* engine, const char* module, asEGMFlags flag ) {
		return engine->GetModule(  );
	}
	int asEngine_DiscardModule( asIScriptEngine* engine, const char* module ) {
		return engine->DiscardModule(  );
	}
	asUINT asEngine_GetModuleCount( asIScriptEngine* engine ) {
		return engine->GetModuleCount(  );
	}
	asIScriptModule* asEngine_GetModuleByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->Module(  );
	}

	// Script functions
	asIScriptFunction* asEngine_GetFunctionById( asIScriptEngine* engine, int funcId ) {
		return engine->Function(  );
	}

	// Type identification
	int asEngine_GetTypeIdByDecl( asIScriptEngine* engine, const char* decl ) {
		return engine->GetTypeIdByDecl(  );
	}
	const char* asEngine_GetTypeDeclaration( asIScriptEngine* engine, int typeId, bool includeNamespace ) {
		return engine->GetTypeDeclaration(  );
	}
	int asEngine_GetSizeOfPrimitiveType( asIScriptEngine* engine, int typeId ) {
		return engine->GetSizeOfPrimitiveType(  );
	}
	asITypeInfo* asEngine_GetTypeInfoById( asIScriptEngine* engine, int typeId ) {
		return engine->e_GetTypeInfoById(  );
	}
	asITypeInfo* asEngine_GetTypeInfoByName( asIScriptEngine* engine, const char* name ) {
		return engine->e_GetTypeInfoByName(  );
	}
	asITypeInfo* asEngine_GetTypeInfoByDecl( asIScriptEngine* engine, const char* decl ) {
		return engine->e_GetTypeInfoByDecl(  );
	}

	// Script execution
	asIScriptContext* asEngine_CreateContext( asIScriptEngine* engine ) {
		return engine->Context(  );
	}
	void* asEngine_CreateScriptObject( asIScriptEngine* engine, const asITypeInfo* type ) {
		return engine->CreateScriptObject(  );
	}
	void* asEngine_CreateScriptObjectCopy( asIScriptEngine* engine, void* obj, const asITypeInfo* type ) {
		return engine->CreateScriptObjectCopy(  );
	}
	void* asEngine_CreateUninitializedScriptObject( asIScriptEngine* engine, const asITypeInfo* type ) {
		return engine->CreateUninitializedScriptObject(  );
	}
	asIScriptFunction* asEngine_CreateDelegate( asIScriptEngine* engine, asIScriptFunction* func, void* obj ) {
		return engine->Function(  );
	}
	int asEngine_AssignScriptObject( asIScriptEngine* engine, void* dstObj, void* srcObj, const asITypeInfo* type ) {
		return engine->AssignScriptObject(  );
	}
	void asEngine_ReleaseScriptObject( asIScriptEngine* engine, void* obj, const asITypeInfo* type ) {
		return engine->ReleaseScriptObject(  );
	}
	void asEngine_AddRefScriptObject( asIScriptEngine* engine, void* obj, const asITypeInfo* type ) {
		return engine->AddRefScriptObject(  );
	}
	int asEngine_RefCastObject( asIScriptEngine* engine, void* obj, asITypeInfo* fromType, asITypeInfo* toType, void** newPtr, bool useOnlyImplicitCast ) {
		return engine->RefCastObject(  );
	}
	asILockableSharedBool* asEngine_GetWeakRefFlagOfScriptObject( asIScriptEngine* engine, void* obj, const asITypeInfo* type ) {
		return engine->leSharedBool(  );
	}

	// Context pooling
	asIScriptContext* asEngine_RequestContext( asIScriptEngine* engine ) {
		return engine->Context(  );
	}
	void asEngine_ReturnContext( asIScriptEngine* engine, asIScriptContext* ctx ) {
		return engine->ReturnContext(  );
	}
	int asEngine_SetContextCallbacks( asIScriptEngine* engine, asREQUESTCONTEXTFUNC_t requestCtx, asRETURNCONTEXTFUNC_t returnCtx, void* param ) {
		return engine->SetContextCallbacks(  );
	}

	// String interpretation
	asETokenClass asEngine_ParseToken( asIScriptEngine* engine, const char* string, size_t stringLength, asUINT* tokenLength ) {
		return engine->lass(  );
	}

	// Garbage collection
	int asEngine_GarbageCollect( asIScriptEngine* engine, asDWORD flags, asUINT numIterations ) {
		return engine->GarbageCollect(  );
	}
	void asEngine_GetGCStatistics( asIScriptEngine* engine, asUINT* currentSize, asUINT* totalDestroyed, asUINT* totalDetected, asUINT* newObjects, asUINT* totalNewDestroyed ) {
		return engine->GetGCStatistics(  );
	}
	int asEngine_NotifyGarbageCollectorOfNewObject( asIScriptEngine* engine, void* obj, asITypeInfo* type ) {
		return engine->NotifyGarbageCollectorOfNewObject(  );
	}
	int asEngine_GetObjectInGC( asIScriptEngine* engine, asUINT idx, asUINT* seqNbr, void** obj, asITypeInfo** type ) {
		return engine->GetObjectInGC(  );
	}
	void asEngine_GCEnumCallback( asIScriptEngine* engine, void* reference ) {
		return engine->GCEnumCallback(  );
	}
	void asEngine_ForwardGCEnumReferences( asIScriptEngine* engine, void* ref, asITypeInfo* type ) {
		return engine->ForwardGCEnumReferences(  );
	}
	void asEngine_ForwardGCReleaseReferences( asIScriptEngine* engine, void* ref, asITypeInfo* type ) {
		return engine->ForwardGCReleaseReferences(  );
	}
	void asEngine_SetCircularRefDetectedCallback( asIScriptEngine* engine, asCIRCULARREFFUNC_t callback, void* param ) {
		return engine->SetCircularRefDetectedCallback(  );
	}

	// User data
	void* asEngine_SetUserData( asIScriptEngine* engine, void* data, asPWORD type ) {
		return engine->SetUserData(  );
	}
	void* asEngine_GetUserData( asIScriptEngine* engine, asPWORD type ) {
		return engine->GetUserData(  );
	}
	void asEngine_SetEngineUserDataCleanupCallback( asIScriptEngine* engine, asCLEANENGINEFUNC_t callback, asPWORD type ) {
		return engine->SetEngineUserDataCleanupCallback(  );
	}
	void asEngine_SetModuleUserDataCleanupCallback( asIScriptEngine* engine, asCLEANMODULEFUNC_t callback, asPWORD type ) {
		return engine->SetModuleUserDataCleanupCallback(  );
	}
	void asEngine_SetContextUserDataCleanupCallback( asIScriptEngine* engine, asCLEANCONTEXTFUNC_t callback, asPWORD type ) {
		return engine->SetContextUserDataCleanupCallback(  );
	}
	void asEngine_SetFunctionUserDataCleanupCallback( asIScriptEngine* engine, asCLEANFUNCTIONFUNC_t callback, asPWORD type ) {
		return engine->SetFunctionUserDataCleanupCallback(  );
	}
	void asEngine_SetTypeInfoUserDataCleanupCallback( asIScriptEngine* engine, asCLEANTYPEINFOFUNC_t callback, asPWORD type ) {
		return engine->SetTypeInfoUserDataCleanupCallback(  );
	}
	void asEngine_SetScriptObjectUserDataCleanupCallback( asIScriptEngine* engine, asCLEANSCRIPTOBJECTFUNC_t callback, asPWORD type ) {
		return engine->SetScriptObjectUserDataCleanupCallback(  );
	}

	// Exception handling
	int asEngine_SetTranslateAppExceptionCallback( asIScriptEngine* engine, asFUNCTION_t callback, void* param, int callConv ) {
		return engine->SetTranslateAppExceptionCallback(  );
	}
	// endregion Interface declarations - engine

	// region Interface declarations - module
	asIScriptEngine* asModule_GetEngine( asIScriptModule* module ) {
		module->
	}
	void asModule_SetName( asIScriptModule* module, const char* name ) {
		module->
	}
	const char* asModule_GetName( asIScriptModule* module ) {
		module->
	}
	void asModule_Discard( asIScriptModule* module ) {
		module->
	}

	// Compilation
	int asModule_AddScriptSection( asIScriptModule* module, const char* name, const char* code, size_t codeLength, int lineOffset ) {
		module->
	}
	int asModule_Build( asIScriptModule* module ) {
		module->
	}
	int asModule_CompileFunction( asIScriptModule* module, const char* sectionName, const char* code, int lineOffset, asDWORD compileFlags,
										 asIScriptFunction** outFunc ) {
		 {->
	}
	int asModule_CompileGlobalVar( asIScriptModule* module, const char* sectionName, const char* code, int lineOffset ) {
		module->
	}
	asDWORD asModule_SetAccessMask( asIScriptModule* module, asDWORD accessMask ) {
		module->
	}
	int asModule_SetDefaultNamespace( asIScriptModule* module, const char* nameSpace ) {
		module->
	}
	const char* asModule_GetDefaultNamespace( asIScriptModule* module ) {
		module->
	}

	// Functions
	asUINT asModule_GetFunctionCount( asIScriptModule* module ) {
		module->
	}
	asIScriptFunction* asModule_GetFunctionByIndex( asIScriptModule* module, asUINT index ) {
		module->
	}
	asIScriptFunction* asModule_GetFunctionByDecl( asIScriptModule* module, const char* decl ) {
		module->
	}
	asIScriptFunction* asModule_GetFunctionByName( asIScriptModule* module, const char* name ) {
		module->
	}
	int asModule_RemoveFunction( asIScriptModule* module, asIScriptFunction* func ) {
		module->
	}

	// Global variables
	int asModule_ResetGlobalVars( asIScriptModule* module, asIScriptContext* ctx ) {
		module->
	}
	asUINT asModule_GetGlobalVarCount( asIScriptModule* module ) {
		module->
	}
	int asModule_GetGlobalVarIndexByName( asIScriptModule* module, const char* name ) {
		module->
	}
	int asModule_GetGlobalVarIndexByDecl( asIScriptModule* module, const char* decl ) {
		module->
	}
	const char* asModule_GetGlobalVarDeclaration( asIScriptModule* module, asUINT index, bool includeNamespace = false ) {
		module->
	}
	int asModule_GetGlobalVar( asIScriptModule* module, asUINT index, const char** name, const char** nameSpace, int* typeId, bool* isConst ) {
		module->
	}
	void* asModule_GetAddressOfGlobalVar( asIScriptModule* module, asUINT index ) {
		module->
	}
	int asModule_RemoveGlobalVar( asIScriptModule* module, asUINT index ) {
		module->
	}

	// Type identification
	asUINT asModule_GetObjectTypeCount( asIScriptModule* module ) {
		module->
	}
	asITypeInfo* asModule_GetObjectTypeByIndex( asIScriptModule* module, asUINT index ) {
		module->
	}
	int asModule_GetTypeIdByDecl( asIScriptModule* module, const char* decl ) {
		module->
	}
	asITypeInfo* asModule_GetTypeInfoByName( asIScriptModule* module, const char* name ) {
		module->
	}
	asITypeInfo* asModule_GetTypeInfoByDecl( asIScriptModule* module, const char* decl ) {
		module->
	}

	// Enums
	asUINT asModule_GetEnumCount( asIScriptModule* module ) {
		module->
	}
	asITypeInfo* asModule_GetEnumByIndex( asIScriptModule* module, asUINT index ) {
		module->
	}

	// Typedefs
	asUINT asModule_GetTypedefCount( asIScriptModule* module ) {
		module->
	}
	asITypeInfo* asModule_GetTypedefByIndex( asIScriptModule* module, asUINT index ) {
		module->
	}

	// Dynamic binding between modules
	asUINT asModule_GetImportedFunctionCount( asIScriptModule* module ) {
		module->
	}
	int asModule_GetImportedFunctionIndexByDecl( asIScriptModule* module, const char* decl ) {
		module->
	}
	const char* asModule_GetImportedFunctionDeclaration( asIScriptModule* module, asUINT importIndex ) {
		module->
	}
	const char* asModule_GetImportedFunctionSourceModule( asIScriptModule* module, asUINT importIndex ) {
		module->
	}
	int asModule_BindImportedFunction( asIScriptModule* module, asUINT importIndex, asIScriptFunction* func ) {
		module->
	}
	int asModule_UnbindImportedFunction( asIScriptModule* module, asUINT importIndex ) {
		module->
	}
	int asModule_BindAllImportedFunctions( asIScriptModule* module ) {
		module->
	}
	int asModule_UnbindAllImportedFunctions( asIScriptModule* module ) {
		module->
	}

	// Byte code saving and loading
	int asModule_SaveByteCode( asIScriptModule* module, asIBinaryStream* out, bool stripDebugInfo ) {
		module->
	}
	int asModule_LoadByteCode( asIScriptModule* module, asIBinaryStream* in, bool* wasDebugInfoStripped ) {
		module->
	}

	// User data
	void* asModule_SetUserData( asIScriptModule* module, void* data, asPWORD type ) {
		module->
	}
	void* asModule_GetUserData( asIScriptModule* module, asPWORD type ) {
		module->
	}
	// endregion Interface declarations - module

	// region Interface declarations - context
	// Memory management
	int asContext_AddRef( asIScriptModule* module ) {
		module->
	}
	int asContext_Release( asIScriptModule* module ) {
		module->
	}

	// Miscellaneous
	asIScriptEngine* asContext_GetEngine( asIScriptModule* module ) {
		module->
	}

	// Execution
	int asContext_Prepare( asIScriptModule* module, asIScriptFunction* func ) {
		module->
	}
	int asContext_Unprepare( asIScriptModule* module ) {
		module->
	}
	int asContext_Execute( asIScriptModule* module ) {
		module->
	}
	int asContext_Abort( asIScriptModule* module ) {
		module->
	}
	int asContext_Suspend( asIScriptModule* module ) {
		module->
	}
	asEContextState asContext_GetState( asIScriptModule* module ) {
		module->
	}
	int asContext_PushState( asIScriptModule* module ) {
		module->
	}
	int asContext_PopState( asIScriptModule* module ) {
		module->
	}
	bool asContext_IsNested( asIScriptModule* module, asUINT* nestCount ) {
		module->
	}

	// Object pointer for calling class methods
	int asContext_SetObject( asIScriptModule* module, void* obj ) {
		module->
	}

	// Arguments
	int asContext_SetArgByte( asIScriptModule* module, asUINT arg, asBYTE value ) {
		module->
	}
	int asContext_SetArgWord( asIScriptModule* module, asUINT arg, asWORD value ) {
		module->
	}
	int asContext_SetArgDWord( asIScriptModule* module, asUINT arg, asDWORD value ) {
		module->
	}
	int asContext_SetArgQWord( asIScriptModule* module, asUINT arg, asQWORD value ) {
		module->
	}
	int asContext_SetArgFloat( asIScriptModule* module, asUINT arg, float value ) {
		module->
	}
	int asContext_SetArgDouble( asIScriptModule* module, asUINT arg, double value ) {
		module->
	}
	int asContext_SetArgAddress( asIScriptModule* module, asUINT arg, void* addr ) {
		module->
	}
	int asContext_SetArgObject( asIScriptModule* module, asUINT arg, void* obj ) {
		module->
	}
	int asContext_SetArgVarType( asIScriptModule* module, asUINT arg, void* ptr, int typeId ) {
		module->
	}
	void* asContext_GetAddressOfArg( asIScriptModule* module, asUINT arg ) {
		module->
	}

	// Return value
	asBYTE asContext_GetReturnByte( asIScriptModule* module ) {
		module->
	}
	asWORD asContext_GetReturnWord( asIScriptModule* module ) {
		module->
	}
	asDWORD asContext_GetReturnDWord( asIScriptModule* module ) {
		module->
	}
	asQWORD asContext_GetReturnQWord( asIScriptModule* module ) {
		module->
	}
	float asContext_GetReturnFloat( asIScriptModule* module ) {
		module->
	}
	double asContext_GetReturnDouble( asIScriptModule* module ) {
		module->
	}
	void* asContext_GetReturnAddress( asIScriptModule* module ) {
		module->
	}
	void* asContext_GetReturnObject( asIScriptModule* module ) {
		module->
	}
	void* asContext_GetAddressOfReturnValue( asIScriptModule* module ) {
		module->
	}

	// Exception handling
	int asContext_SetException( asIScriptModule* module, const char* info, bool allowCatch ) {
		module->
	}
	int asContext_GetExceptionLineNumber( asIScriptModule* module, int* column, const char** sectionName ) {
		module->
	}
	asIScriptFunction* asContext_GetExceptionFunction( asIScriptModule* module ) {
		module->
	}
	const char* asContext_GetExceptionString( asIScriptModule* module ) {
		module->
	}
	bool asContext_WillExceptionBeCaught( asIScriptModule* module ) {
		module->
	}
	int asContext_SetExceptionCallback( asIScriptModule* module, asFUNCTION_t callback, void* obj, int callConv ) {
		module->
	}
	void asContext_ClearExceptionCallback( asIScriptModule* module ) {
		module->
	}

	// Debugging
	int asContext_SetLineCallback( asIScriptModule* module, asFUNCTION_t callback, void* obj, int callConv ) {
		module->
	}
	void asContext_ClearLineCallback( asIScriptModule* module ) {
		module->
	}
	asUINT asContext_GetCallstackSize( asIScriptModule* module ) {
		module->
	}
	asIScriptFunction* asContext_GetFunction( asIScriptModule* module, asUINT stackLevel ) {
		module->
	}
	int asContext_GetLineNumber( asIScriptModule* module, asUINT stackLevel, int* column, const char** sectionName ) {
		module->
	}
	int asContext_GetVarCount( asIScriptModule* module, asUINT stackLevel ) {
		module->
	}
	int asContext_GetVar( asIScriptModule* module, asUINT varIndex, asUINT stackLevel, const char** name, int* typeId, asETypeModifiers* typeModifiers, bool* isVarOnHeap, int* stackOffset ) {
		module->
	}
	const char* asContext_GetVarDeclaration( asIScriptModule* module, asUINT varIndex, asUINT stackLevel, bool includeNamespace = false ) {
		module->
	}
	void* asContext_GetAddressOfVar( asIScriptModule* module, asUINT varIndex, asUINT stackLevel, bool dontDereference, bool returnAddressOfUnitializedObjects ) {
		module->
	}
	bool asContext_IsVarInScope( asIScriptModule* module, asUINT varIndex, asUINT stackLevel ) {
		module->
	}
	int asContext_GetThisTypeId( asIScriptModule* module, asUINT stackLevel ) {
		module->
	}
	void* asContext_GetThisPointer( asIScriptModule* module, asUINT stackLevel ) {
		module->
	}
	asIScriptFunction* asContext_GetSystemFunction( asIScriptModule* module ) {
		module->
	}

	// User data
	void* asContext_SetUserData( asIScriptModule* module, void* data, asPWORD type ) {
		module->
	}
	void* asContext_GetUserData( asIScriptModule* module, asPWORD type ) {
		module->
	}

	// Serialization
	int asContext_StartDeserialization( asIScriptModule* module ) {
		module->
	}
	int asContext_FinishDeserialization( asIScriptModule* module ) {
		module->
	}
	int asContext_PushFunction( asIScriptModule* module, asIScriptFunction* func, void* object ) {
		module->
	}
	int asContext_GetStateRegisters( asIScriptModule* module, asUINT stackLevel, asIScriptFunction** callingSystemFunction, asIScriptFunction** initialFunction, asDWORD* origStackPointer, asDWORD* argumentsSize, asQWORD* valueRegister, void** objectRegister, asITypeInfo** objectTypeRegister ) {
		module->
	}
	int asContext_GetCallStateRegisters( asIScriptModule* module, asUINT stackLevel, asDWORD* stackFramePointer, asIScriptFunction** currentFunction, asDWORD* programPointer, asDWORD* stackPointer, asDWORD* stackIndex ) {
		module->
	}
	int asContext_SetStateRegisters( asIScriptModule* module, asUINT stackLevel, asIScriptFunction* callingSystemFunction, asIScriptFunction* initialFunction, asDWORD origStackPointer, asDWORD argumentsSize, asQWORD valueRegister, void* objectRegister, asITypeInfo* objectTypeRegister ) {
		module->
	}
	int asContext_SetCallStateRegisters( asIScriptModule* module, asUINT stackLevel, asDWORD stackFramePointer, asIScriptFunction* currentFunction, asDWORD programPointer, asDWORD stackPointer, asDWORD stackIndex ) {
		module->
	}
	int asContext_GetArgsOnStackCount( asIScriptModule* module, asUINT stackLevel ) {
		module->
	}
	int asContext_GetArgOnStack( asIScriptModule* module, asUINT stackLevel, asUINT arg, int* typeId, asUINT* flags, void** address ) {
		module->
	}
	// endregion Interface declarations - context

	// region Interface declarations - generic
	// Miscellaneous
	asIScriptEngine* asGeneric_GetEngine( asIScriptGeneric* generic ) {
		generic->
	}
	asIScriptFunction* asGeneric_GetFunction( asIScriptGeneric* generic ) {
		generic->
	}
	void* asGeneric_GetAuxiliary( asIScriptGeneric* generic ) {
		generic->
	}

	// Object
	void* asGeneric_GetObject( asIScriptGeneric* generic ) {
		generic->
	}
	int asGeneric_GetObjectTypeId( asIScriptGeneric* generic ) {
		generic->
	}

	// Arguments
	int asGeneric_GetArgCount( asIScriptGeneric* generic ) {
		generic->
	}
	int asGeneric_GetArgTypeId( asIScriptGeneric* generic, asUINT arg, asDWORD* flags ) {
		generic->
	}
	asBYTE asGeneric_GetArgByte( asIScriptGeneric* generic, asUINT arg ) {
		generic->
	}
	asWORD asGeneric_GetArgWord( asIScriptGeneric* generic, asUINT arg ) {
		generic->
	}
	asDWORD asGeneric_GetArgDWord( asIScriptGeneric* generic, asUINT arg ) {
		generic->
	}
	asQWORD asGeneric_GetArgQWord( asIScriptGeneric* generic, asUINT arg ) {
		generic->
	}
	float asGeneric_GetArgFloat( asIScriptGeneric* generic, asUINT arg ) {
		generic->
	}
	double asGeneric_GetArgDouble( asIScriptGeneric* generic, asUINT arg ) {
		generic->
	}
	void* asGeneric_GetArgAddress( asIScriptGeneric* generic, asUINT arg ) {
		generic->
	}
	void* asGeneric_GetArgObject( asIScriptGeneric* generic, asUINT arg ) {
		generic->
	}
	void* asGeneric_GetAddressOfArg( asIScriptGeneric* generic, asUINT arg ) {
		generic->
	}

	// Return value
	int asGeneric_GetReturnTypeId( asIScriptGeneric* generic, asDWORD* flags ) {
		generic->
	}
	int asGeneric_SetReturnByte( asIScriptGeneric* generic, asBYTE val ) {
		generic->
	}
	int asGeneric_SetReturnWord( asIScriptGeneric* generic, asWORD val ) {
		generic->
	}
	int asGeneric_SetReturnDWord( asIScriptGeneric* generic, asDWORD val ) {
		generic->
	}
	int asGeneric_SetReturnQWord( asIScriptGeneric* generic, asQWORD val ) {
		generic->
	}
	int asGeneric_SetReturnFloat( asIScriptGeneric* generic, float val ) {
		generic->
	}
	int asGeneric_SetReturnDouble( asIScriptGeneric* generic, double val ) {
		generic->
	}
	int asGeneric_SetReturnAddress( asIScriptGeneric* generic, void* addr ) {
		generic->
	}
	int asGeneric_SetReturnObject( asIScriptGeneric* generic, void* obj ) {
		generic->
	}
	void* asGeneric_GetAddressOfReturnLocation( asIScriptGeneric* generic ) {
		generic->
	}
	// endregion Interface declarations - generic

	// region Interface declarations - object
	// Memory management
	int asObject_AddRef( asIScriptObject* object ) {
		object->
	}
	int asObject_Release( asIScriptObject* object ) {
		object->
	}
	asILockableSharedBool* asObject_GetWeakRefFlag( asIScriptObject* object ) {
		object->
	}

	// Type info
	int asObject_GetTypeId( asIScriptObject* object ) {
		object->
	}
	asITypeInfo* asObject_GetObjectType( asIScriptObject* object ) {
		object->
	}

	// Class properties
	asUINT asObject_GetPropertyCount( asIScriptObject* object ) {
		object->
	}
	int asObject_GetPropertyTypeId( asIScriptObject* object, asUINT prop ) {
		object->
	}
	const char* asObject_GetPropertyName( asIScriptObject* object, asUINT prop ) {
		object->
	}
	void* asObject_GetAddressOfProperty( asIScriptObject* object, asUINT prop ) {
		object->
	}

	// Miscellaneous
	asIScriptEngine* asObject_GetEngine( asIScriptObject* object ) {
		object->
	}
	int asObject_CopyFrom( asIScriptObject* object, const asIScriptObject* other ) {
		object->
	}

	// User data
	void* asObject_SetUserData( asIScriptObject* object, void* data, asPWORD type ) {
		object->
	}
	void* asObject_GetUserData( asIScriptObject* object, asPWORD type ) {
		object->
	}
	// endregion Interface declarations - object

	// region Interface declarations - type info
	// Miscellaneous
	asIScriptEngine* asTypeInfo_GetEngine( asITypeInfo* info ) {
		info->
	}
	const char* asTypeInfo_GetConfigGroup( asITypeInfo* info ) {
		info->
	}
	asDWORD asTypeInfo_GetAccessMask( asITypeInfo* info ) {
		info->
	}
	asIScriptModule* asTypeInfo_GetModule( asITypeInfo* info ) {
		info->
	}

	// Memory management
	int asTypeInfo_AddRef( asITypeInfo* info ) {
		info->
	}
	int asTypeInfo_Release( asITypeInfo* info ) {
		info->
	}

	// Type info
	const char* asTypeInfo_GetName( asITypeInfo* info ) {
		info->
	}
	const char* asTypeInfo_GetNamespace( asITypeInfo* info ) {
		info->
	}
	asITypeInfo* asTypeInfo_GetBaseType( asITypeInfo* info ) {
		info->
	}
	bool asTypeInfo_DerivesFrom( asITypeInfo* info, const asITypeInfo* objType ) {
		info->
	}
	asDWORD asTypeInfo_GetFlags( asITypeInfo* info ) {
		info->
	}
	asUINT asTypeInfo_GetSize( asITypeInfo* info ) {
		info->
	}
	int asTypeInfo_GetTypeId( asITypeInfo* info ) {
		info->
	}
	int asTypeInfo_GetSubTypeId( asITypeInfo* info, asUINT subTypeIndex ) {
		info->
	}
	asITypeInfo* asTypeInfo_GetSubType( asITypeInfo* info, asUINT subTypeIndex ) {
		info->
	}
	asUINT asTypeInfo_GetSubTypeCount( asITypeInfo* info ) {
		info->
	}

	// Interfaces
	asUINT asTypeInfo_GetInterfaceCount( asITypeInfo* info ) {
		info->
	}
	asITypeInfo* asTypeInfo_GetInterface( asITypeInfo* info, asUINT index ) {
		info->
	}
	bool asTypeInfo_Implements( asITypeInfo* info, const asITypeInfo* objType ) {
		info->
	}

	// Factories
	asUINT asTypeInfo_GetFactoryCount( asITypeInfo* info ) {
		info->
	}
	asIScriptFunction* asTypeInfo_GetFactoryByIndex( asITypeInfo* info, asUINT index ) {
		info->
	}
	asIScriptFunction* asTypeInfo_GetFactoryByDecl( asITypeInfo* info, const char* decl ) {
		info->
	}

	// Methods
	asUINT asTypeInfo_GetMethodCount( asITypeInfo* info ) {
		info->
	}
	asIScriptFunction* asTypeInfo_GetMethodByIndex( asITypeInfo* info, asUINT index, bool getVirtual ) {
		info->
	}
	asIScriptFunction* asTypeInfo_GetMethodByName( asITypeInfo* info, const char* name, bool getVirtual ) {
		info->
	}
	asIScriptFunction* asTypeInfo_GetMethodByDecl( asITypeInfo* info, const char* decl, bool getVirtual ) {
		info->
	}

	// Properties
	asUINT asTypeInfo_GetPropertyCount( asITypeInfo* info ) {
		info->
	}
	int asTypeInfo_GetProperty( asITypeInfo* info, asUINT index, const char** name, int* typeId, bool* isPrivate, bool* isProtected, int* offset, bool* isReference, asDWORD* accessMask, int* compositeOffset, bool* isCompositeIndirect ) {
		info->
	}
	const char* asTypeInfo_GetPropertyDeclaration( asITypeInfo* info, asUINT index, bool includeNamespace ) {
		info->
	}

	// Behaviours
	asUINT asTypeInfo_GetBehaviourCount( asITypeInfo* info ) {
		info->
	}
	asIScriptFunction* asTypeInfo_GetBehaviourByIndex( asITypeInfo* info, asUINT index, asEBehaviours* outBehaviour ) {
		info->
	}

	// Child types
	asUINT asTypeInfo_GetChildFuncdefCount( asITypeInfo* info ) {
		info->
	}
	asITypeInfo* asTypeInfo_GetChildFuncdef( asITypeInfo* info, asUINT index ) {
		info->
	}
	asITypeInfo* asTypeInfo_GetParentType( asITypeInfo* info ) {
		info->
	}

	// Enums
	asUINT asTypeInfo_GetEnumValueCount( asITypeInfo* info ) {
		info->
	}
	const char* asTypeInfo_GetEnumValueByIndex( asITypeInfo* info, asUINT index, int* outValue ) {
		info->
	}

	// Typedef
	int asTypeInfo_GetTypedefTypeId( asITypeInfo* info ) {
		info->
	}

	// Funcdef
	asIScriptFunction* asTypeInfo_GetFuncdefSignature( asITypeInfo* info ) {
		info->
	}

	// User data
	void* asTypeInfo_SetUserData( asITypeInfo* info, void* data, asPWORD type ) {
		info->
	}
	void* asTypeInfo_GetUserData( asITypeInfo* info, asPWORD type ) {
		info->
	}
	// endregion Interface declarations - type info

	// region Interface declarations - function
	asIScriptEngine* asFunction_GetEngine( asIScriptFunction* function ) {
		function->
	}

	// Memory management
	int asFunction_AddRef( asIScriptFunction* function ) {
		function->
	}
	int asFunction_Release( asIScriptFunction* function ) {
		function->
	}

	// Miscellaneous
	int asFunction_GetId( asIScriptFunction* function ) {
		function->
	}
	asEFuncType asFunction_GetFuncType( asIScriptFunction* function ) {
		function->
	}
	const char* asFunction_GetModuleName( asIScriptFunction* function ) {
		function->
	}
	asIScriptModule* asFunction_GetModule( asIScriptFunction* function ) {
		function->
	}
	const char* asFunction_GetScriptSectionName( asIScriptFunction* function ) {
		function->
	}
	const char* asFunction_GetConfigGroup( asIScriptFunction* function ) {
		function->
	}
	asDWORD asFunction_GetAccessMask( asIScriptFunction* function ) {
		function->
	}
	void* asFunction_GetAuxiliary( asIScriptFunction* function ) {
		function->
	}

	// Function signature
	asITypeInfo* asFunction_GetObjectType( asIScriptFunction* function ) {
		function->
	}
	const char* asFunction_GetObjectName( asIScriptFunction* function ) {
		function->
	}
	const char* asFunction_GetName( asIScriptFunction* function ) {
		function->
	}
	const char* asFunction_GetNamespace( asIScriptFunction* function ) {
		function->
	}
	const char* asFunction_GetDeclaration( asIScriptFunction* function, bool includeObjectName, bool includeNamespace, bool includeParamNames ) {
		function->
	}
	bool asFunction_IsReadOnly( asIScriptFunction* function ) {
		function->
	}
	bool asFunction_IsPrivate( asIScriptFunction* function ) {
		function->
	}
	bool asFunction_IsProtected( asIScriptFunction* function ) {
		function->
	}
	bool asFunction_IsFinal( asIScriptFunction* function ) {
		function->
	}
	bool asFunction_IsOverride( asIScriptFunction* function ) {
		function->
	}
	bool asFunction_IsShared( asIScriptFunction* function ) {
		asIScriptFunction->
	}
	bool asFunction_IsExplicit( asIScriptFunction* function ) {
		function->
	}
	bool asFunction_IsProperty( asIScriptFunction* function ) {
		function->
	}
	asUINT asFunction_GetParamCount( asIScriptFunction* function ) {
		function->
	}
	int asFunction_GetParam( asIScriptFunction* function, asUINT index, int* typeId, asDWORD* flags, const char** name, const char** defaultArg ) {
		function->
	}
	int asFunction_GetReturnTypeId( asIScriptFunction* function, asDWORD* flags ) {
		function->
	}

	// Type id for function pointers
	int asFunction_GetTypeId( asIScriptFunction* function ) {
		function->
	}
	bool asFunction_IsCompatibleWithTypeId( asIScriptFunction* function, int typeId ) {
		function->
	}

	// Delegates
	void* asFunction_GetDelegateObject( asIScriptFunction* function ) {
		function->
	}
	asITypeInfo* asFunction_GetDelegateObjectType( asIScriptFunction* function ) {
		function->
	}
	asIScriptFunction* asFunction_GetDelegateFunction( asIScriptFunction* function ) {
		function->
	}

	// Debug information
	asUINT asFunction_GetVarCount( asIScriptFunction* function ) {
		function->
	}
	int asFunction_GetVar( asIScriptFunction* function, asUINT index, const char** name, int* typeId ) {
		function->
	}
	const char* asFunction_GetVarDecl( asIScriptFunction* function, asUINT index, bool includeNamespace ) {
		function->
	}
	int asFunction_FindNextLineWithCode( asIScriptFunction* function, int line ) {
		function->
	}

	// For JIT compilation
	asDWORD* asFunction_GetByteCode( asIScriptFunction* function, asUINT* length ) {
		function->
	}

	// User data
	void* asFunction_SetUserData( asIScriptFunction* function, void* userData, asPWORD type ) {
		function->
	}
	void* asFunction_GetUserData( asIScriptFunction* function, asPWORD type ) {
		function->
	}
	// endregion Interface declarations - function

	// region Interface declarations - binary stream
	int asBinaryStream_Read( asIBinaryStream* stream, void* ptr, asUINT size ) {
		stream->
	}
	int asBinaryStream_Write( asIBinaryStream* stream, const void* ptr, asUINT size ) {
		stream->
	}
	// endregion Interface declarations - binary stream

	// region Interface declarations - lockable shared bool
	// Memory management
	int asLockableSharedBool_AddRef( asILockableSharedBool* lockable ) {
		lockable->
	}
	int asLockableSharedBool_Release( asILockableSharedBool* lockable ) {
		lockable->
	}

	// Value
	bool asLockableSharedBool_Get( asILockableSharedBool* lockable ) {
		lockable->
	}
	void asLockableSharedBool_Set( asILockableSharedBool* lockable, bool val ) {
		lockable->
	}

	// Thread management
	void asLockableSharedBool_Lock( asILockableSharedBool* lockable ) {
		lockable->
	}
	void asLockableSharedBool_Unlock( asILockableSharedBool* lockable ) {
		lockable->
	}
	// endregion Interface declarations - lockable shared bool

	// region Interface declarations - string factory
	const void* asStringFactory_GetStringConstant( asIStringFactory* factory, const char* data, asUINT length ) {
		factory->
	}
	int asStringFactory_ReleaseStringConstant( asIStringFactory* factory, const void* str ) {
		factory->
	}
	int asStringFactory_GetRawStringData( asIStringFactory* factory, const void* str, char* data, asUINT* length ) {
		factory->
	}
	// endregion Interface declarations - string factory
}
