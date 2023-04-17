//
// Created by Firmament on 19/03/2023.
//

#include "../vendor/sdk/angelscript/include/angelscript.h"


struct asStringFactory {
	const void* ( *getStringConstant )( const char* data, asUINT length, void* user );
	int ( *releaseStringConstant )( const void* str, void* user );
	int ( *getRawStringData )( const void* str, char* data, asUINT* length, void* user );
	void* user;
};

struct asBinaryStream {
	int ( *read )( void* ptr, asUINT size, void* user );
	int ( *write )( const void* ptr, asUINT size, void* user );
	void* user;
};

struct asJITCompiler {
	int ( *compileFunction )( asIScriptFunction* function, asJITFunction* output, void* user );
	int ( *releaseJITFunction )( asJITFunction func, void* user );
	void* user;
};

struct asThreadManager {
	void* user;
};

enum asBOOL_t : unsigned char { asFALSE = 0, asTRUE = 1 };


class asCStringFactory : public asIStringFactory {
private:
	asStringFactory* impl;
public:
	explicit asCStringFactory( asStringFactory* factory ) : impl( factory ) { }

	const void* GetStringConstant( const char* data, asUINT length ) override {
		return this->impl->getStringConstant( data, length, this->impl->user );
	};
	int ReleaseStringConstant( const void* str ) override {
		return this->impl->releaseStringConstant( str, this->impl->user );
	};
	int GetRawStringData( const void* str, char* data, asUINT* length ) const override {
		return this->impl->getRawStringData( str, data, length, this->impl->user );
	};
};

class asCBinaryStream : public asIBinaryStream {
private:
	asBinaryStream* impl;
public:
	explicit asCBinaryStream( asBinaryStream* stream ) : impl( stream ) { }

	int Write( const void* ptr, asUINT size ) override {
		return this->impl->write( ptr, size, this->impl->user );
	}
	int Read( void* ptr, asUINT size ) override {
		return this->impl->read( ptr, size, this->impl->user );
	}
};

class asCJITCompiler : public asIJITCompiler {
private:
	asJITCompiler* impl;
public:
	explicit asCJITCompiler( asJITCompiler* compiler ) : impl( compiler ) { };
	int CompileFunction( asIScriptFunction* function, asJITFunction* output ) override {
		return this->impl->compileFunction( function, output, this->impl->user );
	};
	void ReleaseJITFunction( asJITFunction func ) override {
		this->impl->releaseJITFunction( func, this->impl->user );
	};
	explicit operator asJITCompiler*() {
		return this->impl;
	};
};

class asCThreadManager : public asIJITCompiler {
private:
	asThreadManager* impl;
public:
	explicit asCThreadManager( asThreadManager* manager ) : impl( manager ) { };

	explicit operator asThreadManager*() {
		return this->impl;
	};
};

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
	int asEngine_SetMessageCallback( asIScriptEngine* engine, asFUNCTION_t* callback, void* obj, asDWORD callConv ) {
		return engine->SetMessageCallback( asFUNCTION( callback ), obj, callConv );
	}
	int asEngine_ClearMessageCallback( asIScriptEngine* engine ) {
		return engine->ClearMessageCallback();
	}
	int asEngine_WriteMessage( asIScriptEngine* engine, char* section, int row, int col, asEMsgType type, char* message ) {
		return engine->WriteMessage( section, row, col, type, message );
	}

	// JIT Compiler
	int asEngine_SetJITCompiler( asIScriptEngine* engine, asJITCompiler* compiler ) {
		return engine->SetJITCompiler( new asCJITCompiler( compiler ) );
	}
	asJITCompiler* asEngine_GetJITCompiler( asIScriptEngine* engine ) {
		return (asJITCompiler*) (asCJITCompiler*) engine->GetJITCompiler();
	}

	// Global functions
	int asEngine_RegisterGlobalFunction( asIScriptEngine* engine, char* declaration, asFUNCTION_t* funcPointer, asDWORD callConv, void* auxiliary ) {
		return engine->RegisterGlobalFunction( declaration, asFUNCTION( funcPointer ), callConv, auxiliary );
	}
	asUINT asEngine_GetGlobalFunctionCount( asIScriptEngine* engine ) {
		return engine->GetGlobalFunctionCount();
	}
	asIScriptFunction* asEngine_GetGlobalFunctionByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->GetGlobalFunctionByIndex( index );
	}
	asIScriptFunction* asEngine_GetGlobalFunctionByDecl( asIScriptEngine* engine, char* declaration ) {
		return engine->GetGlobalFunctionByDecl( declaration );
	}

	// Global properties
	int asEngine_RegisterGlobalProperty( asIScriptEngine* engine, const char* declaration, void* pointer ) {
		return engine->RegisterGlobalProperty( declaration, pointer );
	}
	asUINT asEngine_GetGlobalPropertyCount( asIScriptEngine* engine ) {
		return engine->GetGlobalPropertyCount();
	}
	int asEngine_GetGlobalPropertyByIndex( asIScriptEngine* engine, asUINT index, const char** name, const char** nameSpace, int* typeId, asBOOL_t* isConst, const char** configGroup, void** pointer, asDWORD* accessMask ) {
		return engine->GetGlobalPropertyByIndex( index, name, nameSpace, typeId, reinterpret_cast<bool*>( isConst ), configGroup, pointer, accessMask );
	}
	int asEngine_GetGlobalPropertyIndexByName( asIScriptEngine* engine, const char* name ) {
		return engine->GetGlobalPropertyIndexByName( name );
	}
	int asEngine_GetGlobalPropertyIndexByDecl( asIScriptEngine* engine, const char* decl ) {
		return engine->GetGlobalPropertyIndexByDecl( decl );
	}

	// Object types
	int asEngine_RegisterObjectType( asIScriptEngine* engine, const char* obj, int byteSize, asDWORD flags ) {
		return engine->RegisterObjectType( obj, byteSize, flags );
	}
	int asEngine_RegisterObjectProperty( asIScriptEngine* engine, const char* obj, const char* declaration, int byteOffset, int compositeOffset, asBOOL_t isCompositeIndirect ) {
		return engine->RegisterObjectProperty( obj, declaration, byteOffset, compositeOffset, isCompositeIndirect );
	}
	int asEngine_RegisterObjectMethod( asIScriptEngine* engine, const char* obj, const char* declaration, asFUNCTION_t* funcPointer, asDWORD callConv, void* auxiliary, int compositeOffset, asBOOL_t isCompositeIndirect ) {
		return engine->RegisterObjectMethod( obj, declaration, asFUNCTION( funcPointer ), callConv, auxiliary, compositeOffset, reinterpret_cast<bool*>( isCompositeIndirect ) );
	}
	int asEngine_RegisterObjectBehaviour( asIScriptEngine* engine, const char* obj, asEBehaviours behaviour, const char* declaration, asFUNCTION_t* funcPointer, asDWORD callConv, void* auxiliary, int compositeOffset, asBOOL_t isCompositeIndirect ) {
		return engine->RegisterObjectBehaviour( obj, behaviour, declaration, asFUNCTION( funcPointer ), callConv, auxiliary, compositeOffset, reinterpret_cast<bool*>( isCompositeIndirect ) );
	}
	int asEngine_RegisterInterface( asIScriptEngine* engine, const char* name ) {
		return engine->RegisterInterface( name );
	}
	int asEngine_RegisterInterfaceMethod( asIScriptEngine* engine, const char* intf, const char* declaration ) {
		return engine->RegisterInterfaceMethod( intf, declaration );
	}
	asUINT asEngine_GetObjectTypeCount( asIScriptEngine* engine ) {
		return engine->GetObjectTypeCount();
	}
	asITypeInfo* asEngine_GetObjectTypeByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->GetObjectTypeByIndex( index );
	}

	// String factory
	int asEngine_RegisterStringFactory( asIScriptEngine* engine, const char* datatype, asStringFactory* factory ) {
		return engine->RegisterStringFactory( datatype, new asCStringFactory(factory) );
	}
	int asEngine_GetStringFactoryReturnTypeId( asIScriptEngine* engine, asDWORD* flags ) {
		return engine->GetStringFactoryReturnTypeId( flags );
	}

	// Default array type
	int asEngine_RegisterDefaultArrayType( asIScriptEngine* engine, const char* type ) {
		return engine->RegisterDefaultArrayType( type );
	}
	int asEngine_GetDefaultArrayTypeId( asIScriptEngine* engine ) {
		return engine->GetDefaultArrayTypeId();
	}

	// Enums
	int asEngine_RegisterEnum( asIScriptEngine* engine, const char* type ) {
		return engine->RegisterEnum( type );
	}
	int asEngine_RegisterEnumValue( asIScriptEngine* engine, const char* type, const char* name, int value ) {
		return engine->RegisterEnumValue( type, name, value );
	}
	asUINT asEngine_GetEnumCount( asIScriptEngine* engine ) {
		return engine->GetEnumCount();
	}
	asITypeInfo* asEngine_GetEnumByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->GetEnumByIndex( index );
	}

	// Funcdefs
	int asEngine_RegisterFuncdef( asIScriptEngine* engine, const char* decl ) {
		return engine->RegisterFuncdef( decl );
	}
	asUINT asEngine_GetFuncdefCount( asIScriptEngine* engine ) {
		return engine->GetFuncdefCount();
	}
	asITypeInfo* asEngine_GetFuncdefByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->GetFuncdefByIndex( index );
	}

	// Typedefs
	int asEngine_RegisterTypedef( asIScriptEngine* engine, const char* type, const char* decl ) {
		return engine->RegisterTypedef( type, decl );
	}
	asUINT asEngine_GetTypedefCount( asIScriptEngine* engine ) {
		return engine->GetTypedefCount();
	}
	asITypeInfo* asEngine_GetTypedefByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->GetTypedefByIndex( index );
	}

	// Configuration groups
	int asEngine_BeginConfigGroup( asIScriptEngine* engine, const char* groupName ) {
		return engine->BeginConfigGroup( groupName );
	}
	int asEngine_EndConfigGroup( asIScriptEngine* engine ) {
		return engine->EndConfigGroup();
	}
	int asEngine_RemoveConfigGroup( asIScriptEngine* engine, const char* groupName ) {
		return engine->RemoveConfigGroup( groupName );
	}
	asDWORD asEngine_SetDefaultAccessMask( asIScriptEngine* engine, asDWORD defaultMask ) {
		return engine->SetDefaultAccessMask( defaultMask );
	}
	int asEngine_SetDefaultNamespace( asIScriptEngine* engine, const char* nameSpace ) {
		return engine->SetDefaultNamespace( nameSpace );
	}
	const char* asEngine_GetDefaultNamespace( asIScriptEngine* engine ) {
		return engine->GetDefaultNamespace();
	}

	// Script modules
	asIScriptModule* asEngine_GetModule( asIScriptEngine* engine, const char* module, asEGMFlags flag ) {
		return engine->GetModule( module, flag );
	}
	int asEngine_DiscardModule( asIScriptEngine* engine, const char* module ) {
		return engine->DiscardModule( module );
	}
	asUINT asEngine_GetModuleCount( asIScriptEngine* engine ) {
		return engine->GetModuleCount();
	}
	asIScriptModule* asEngine_GetModuleByIndex( asIScriptEngine* engine, asUINT index ) {
		return engine->GetModuleByIndex( index );
	}

	// Script functions
	asIScriptFunction* asEngine_GetFunctionById( asIScriptEngine* engine, int funcId ) {
		return engine->GetFunctionById( funcId );
	}

	// Type identification
	int asEngine_GetTypeIdByDecl( asIScriptEngine* engine, const char* decl ) {
		return engine->GetTypeIdByDecl( decl );
	}
	const char* asEngine_GetTypeDeclaration( asIScriptEngine* engine, int typeId, asBOOL_t includeNamespace ) {
		return engine->GetTypeDeclaration( typeId, includeNamespace );
	}
	int asEngine_GetSizeOfPrimitiveType( asIScriptEngine* engine, int typeId ) {
		return engine->GetSizeOfPrimitiveType( typeId );
	}
	asITypeInfo* asEngine_GetTypeInfoById( asIScriptEngine* engine, int typeId ) {
		return engine->GetTypeInfoById( typeId );
	}
	asITypeInfo* asEngine_GetTypeInfoByName( asIScriptEngine* engine, const char* name ) {
		return engine->GetTypeInfoByName( name );
	}
	asITypeInfo* asEngine_GetTypeInfoByDecl( asIScriptEngine* engine, const char* decl ) {
		return engine->GetTypeInfoByDecl( decl );
	}

	// Script execution
	asIScriptContext* asEngine_CreateContext( asIScriptEngine* engine ) {
		return engine->CreateContext();
	}
	void* asEngine_CreateScriptObject( asIScriptEngine* engine, const asITypeInfo* type ) {
		return engine->CreateScriptObject( type );
	}
	void* asEngine_CreateScriptObjectCopy( asIScriptEngine* engine, void* obj, const asITypeInfo* type ) {
		return engine->CreateScriptObjectCopy( obj, type );
	}
	void* asEngine_CreateUninitializedScriptObject( asIScriptEngine* engine, const asITypeInfo* type ) {
		return engine->CreateUninitializedScriptObject( type );
	}
	asIScriptFunction* asEngine_CreateDelegate( asIScriptEngine* engine, asIScriptFunction* func, void* obj ) {
		return engine->CreateDelegate( func, obj );
	}
	int asEngine_AssignScriptObject( asIScriptEngine* engine, void* dstObj, void* srcObj, const asITypeInfo* type ) {
		return engine->AssignScriptObject( dstObj, srcObj, type );
	}
	void asEngine_ReleaseScriptObject( asIScriptEngine* engine, void* obj, const asITypeInfo* type ) {
		return engine->ReleaseScriptObject( obj, type );
	}
	void asEngine_AddRefScriptObject( asIScriptEngine* engine, void* obj, const asITypeInfo* type ) {
		return engine->AddRefScriptObject( obj, type );
	}
	int asEngine_RefCastObject( asIScriptEngine* engine, void* obj, asITypeInfo* fromType, asITypeInfo* toType, void** newPtr, asBOOL_t useOnlyImplicitCast ) {
		return engine->RefCastObject( obj, fromType, toType, newPtr, useOnlyImplicitCast );
	}
	asILockableSharedBool* asEngine_GetWeakRefFlagOfScriptObject( asIScriptEngine* engine, void* obj, const asITypeInfo* type ) {
		return engine->GetWeakRefFlagOfScriptObject( obj, type );
	}

	// Context pooling
	asIScriptContext* asEngine_RequestContext( asIScriptEngine* engine ) {
		return engine->RequestContext();
	}
	void asEngine_ReturnContext( asIScriptEngine* engine, asIScriptContext* ctx ) {
		return engine->ReturnContext( ctx );
	}
	int asEngine_SetContextCallbacks( asIScriptEngine* engine, asREQUESTCONTEXTFUNC_t requestCtx, asRETURNCONTEXTFUNC_t returnCtx, void* param ) {
		return engine->SetContextCallbacks( requestCtx, returnCtx, param );
	}

	// String interpretation
	asETokenClass asEngine_ParseToken( asIScriptEngine* engine, const char* string, size_t stringLength, asUINT* tokenLength ) {
		return engine->ParseToken( string, stringLength, tokenLength );
	}

	// Garbage collection
	int asEngine_GarbageCollect( asIScriptEngine* engine, asDWORD flags, asUINT numIterations ) {
		return engine->GarbageCollect( flags, numIterations );
	}
	void asEngine_GetGCStatistics( asIScriptEngine* engine, asUINT* currentSize, asUINT* totalDestroyed, asUINT* totalDetected, asUINT* newObjects, asUINT* totalNewDestroyed ) {
		return engine->GetGCStatistics( currentSize, totalDestroyed, totalDetected, newObjects, totalNewDestroyed );
	}
	int asEngine_NotifyGarbageCollectorOfNewObject( asIScriptEngine* engine, void* obj, asITypeInfo* type ) {
		return engine->NotifyGarbageCollectorOfNewObject( obj, type );
	}
	int asEngine_GetObjectInGC( asIScriptEngine* engine, asUINT idx, asUINT* seqNbr, void** obj, asITypeInfo** type ) {
		return engine->GetObjectInGC( idx, seqNbr, obj, type );
	}
	void asEngine_GCEnumCallback( asIScriptEngine* engine, void* reference ) {
		return engine->GCEnumCallback( reference );
	}
	void asEngine_ForwardGCEnumReferences( asIScriptEngine* engine, void* ref, asITypeInfo* type ) {
		return engine->ForwardGCEnumReferences( ref, type );
	}
	void asEngine_ForwardGCReleaseReferences( asIScriptEngine* engine, void* ref, asITypeInfo* type ) {
		return engine->ForwardGCReleaseReferences( ref, type );
	}
	void asEngine_SetCircularRefDetectedCallback( asIScriptEngine* engine, asCIRCULARREFFUNC_t callback, void* param ) {
		return engine->SetCircularRefDetectedCallback( callback, param );
	}

	// User data
	void* asEngine_SetUserData( asIScriptEngine* engine, void* data, asPWORD type ) {
		return engine->SetUserData( data, type );
	}
	void* asEngine_GetUserData( asIScriptEngine* engine, asPWORD type ) {
		return engine->GetUserData( type );
	}
	void asEngine_SetEngineUserDataCleanupCallback( asIScriptEngine* engine, asCLEANENGINEFUNC_t callback, asPWORD type ) {
		return engine->SetEngineUserDataCleanupCallback( callback, type );
	}
	void asEngine_SetModuleUserDataCleanupCallback( asIScriptEngine* engine, asCLEANMODULEFUNC_t callback, asPWORD type ) {
		return engine->SetModuleUserDataCleanupCallback( callback, type );
	}
	void asEngine_SetContextUserDataCleanupCallback( asIScriptEngine* engine, asCLEANCONTEXTFUNC_t callback, asPWORD type ) {
		return engine->SetContextUserDataCleanupCallback( callback, type );
	}
	void asEngine_SetFunctionUserDataCleanupCallback( asIScriptEngine* engine, asCLEANFUNCTIONFUNC_t callback, asPWORD type ) {
		return engine->SetFunctionUserDataCleanupCallback( callback, type );
	}
	void asEngine_SetTypeInfoUserDataCleanupCallback( asIScriptEngine* engine, asCLEANTYPEINFOFUNC_t callback, asPWORD type ) {
		return engine->SetTypeInfoUserDataCleanupCallback( callback, type );
	}
	void asEngine_SetScriptObjectUserDataCleanupCallback( asIScriptEngine* engine, asCLEANSCRIPTOBJECTFUNC_t callback, asPWORD type ) {
		return engine->SetScriptObjectUserDataCleanupCallback( callback, type );
	}

	// Exception handling
	int asEngine_SetTranslateAppExceptionCallback( asIScriptEngine* engine, asFUNCTION_t callback, void* param, int callConv ) {
		return engine->SetTranslateAppExceptionCallback( asFUNCTION( callback ), param, callConv );
	}
	// endregion Interface declarations - engine

	// region Interface declarations - module
	asIScriptEngine* asModule_GetEngine( asIScriptModule* module ) {
		return module->GetEngine();
	}
	void asModule_SetName( asIScriptModule* module, const char* name ) {
		module->SetName( name );
	}
	const char* asModule_GetName( asIScriptModule* module ) {
		return module->GetName();
	}
	void asModule_Discard( asIScriptModule* module ) {
		module->Discard();
	}

	// Compilation
	int asModule_AddScriptSection( asIScriptModule* module, const char* name, const char* code, size_t codeLength, int lineOffset ) {
		return module->AddScriptSection( name, code, codeLength, lineOffset );
	}
	int asModule_Build( asIScriptModule* module ) {
		return module->Build();
	}
	int asModule_CompileFunction( asIScriptModule* module, const char* sectionName, const char* code, int lineOffset, asDWORD compileFlags, asIScriptFunction** outFunc ) {
		return module->CompileFunction( sectionName, code, lineOffset, compileFlags, outFunc );
	}
	int asModule_CompileGlobalVar( asIScriptModule* module, const char* sectionName, const char* code, int lineOffset ) {
		return module->CompileGlobalVar( sectionName, code, lineOffset );
	}
	asDWORD asModule_SetAccessMask( asIScriptModule* module, asDWORD accessMask ) {
		return module->SetAccessMask( accessMask );
	}
	int asModule_SetDefaultNamespace( asIScriptModule* module, const char* nameSpace ) {
		return module->SetDefaultNamespace( nameSpace );
	}
	const char* asModule_GetDefaultNamespace( asIScriptModule* module ) {
		return module->GetDefaultNamespace();
	}

	// Functions
	asUINT asModule_GetFunctionCount( asIScriptModule* module ) {
		return module->GetFunctionCount();
	}
	asIScriptFunction* asModule_GetFunctionByIndex( asIScriptModule* module, asUINT index ) {
		return module->GetFunctionByIndex( index );
	}
	asIScriptFunction* asModule_GetFunctionByDecl( asIScriptModule* module, const char* decl ) {
		return module->GetFunctionByDecl( decl );
	}
	asIScriptFunction* asModule_GetFunctionByName( asIScriptModule* module, const char* name ) {
		return module->GetFunctionByName( name );
	}
	int asModule_RemoveFunction( asIScriptModule* module, asIScriptFunction* func ) {
		return module->RemoveFunction( func );
	}

	// Global variables
	int asModule_ResetGlobalVars( asIScriptModule* module, asIScriptContext* ctx ) {
		return module->ResetGlobalVars( ctx );
	}
	asUINT asModule_GetGlobalVarCount( asIScriptModule* module ) {
		return module->GetGlobalVarCount();
	}
	int asModule_GetGlobalVarIndexByName( asIScriptModule* module, const char* name ) {
		return module->GetGlobalVarIndexByName( name );
	}
	int asModule_GetGlobalVarIndexByDecl( asIScriptModule* module, const char* decl ) {
		return module->GetGlobalVarIndexByDecl( decl );
	}
	const char* asModule_GetGlobalVarDeclaration( asIScriptModule* module, asUINT index, asBOOL_t includeNamespace = asFALSE ) {
		return module->GetGlobalVarDeclaration( index, includeNamespace );
	}
	int asModule_GetGlobalVar( asIScriptModule* module, asUINT index, const char** name, const char** nameSpace, int* typeId, asBOOL_t* isConst ) {
		return module->GetGlobalVar( index, name, nameSpace, typeId, reinterpret_cast<bool*>( isConst ) );
	}
	void* asModule_GetAddressOfGlobalVar( asIScriptModule* module, asUINT index ) {
		return module->GetAddressOfGlobalVar( index );
	}
	int asModule_RemoveGlobalVar( asIScriptModule* module, asUINT index ) {
		return module->RemoveGlobalVar( index );
	}

	// Type identification
	asUINT asModule_GetObjectTypeCount( asIScriptModule* module ) {
		return module->GetObjectTypeCount();
	}
	asITypeInfo* asModule_GetObjectTypeByIndex( asIScriptModule* module, asUINT index ) {
		return module->GetObjectTypeByIndex( index );
	}
	int asModule_GetTypeIdByDecl( asIScriptModule* module, const char* decl ) {
		return module->GetTypeIdByDecl( decl );
	}
	asITypeInfo* asModule_GetTypeInfoByName( asIScriptModule* module, const char* name ) {
		return module->GetTypeInfoByName( name );
	}
	asITypeInfo* asModule_GetTypeInfoByDecl( asIScriptModule* module, const char* decl ) {
		return module->GetTypeInfoByDecl( decl );
	}

	// Enums
	asUINT asModule_GetEnumCount( asIScriptModule* module ) {
		return module->GetEnumCount();
	}
	asITypeInfo* asModule_GetEnumByIndex( asIScriptModule* module, asUINT index ) {
		return module->GetEnumByIndex( index );
	}

	// Typedefs
	asUINT asModule_GetTypedefCount( asIScriptModule* module ) {
		return module->GetTypedefCount();
	}
	asITypeInfo* asModule_GetTypedefByIndex( asIScriptModule* module, asUINT index ) {
		return module->GetTypedefByIndex( index );
	}

	// Dynamic binding between modules
	asUINT asModule_GetImportedFunctionCount( asIScriptModule* module ) {
		return module->GetImportedFunctionCount();
	}
	int asModule_GetImportedFunctionIndexByDecl( asIScriptModule* module, const char* decl ) {
		return module->GetImportedFunctionIndexByDecl( decl );
	}
	const char* asModule_GetImportedFunctionDeclaration( asIScriptModule* module, asUINT importIndex ) {
		return module->GetImportedFunctionDeclaration( importIndex );
	}
	const char* asModule_GetImportedFunctionSourceModule( asIScriptModule* module, asUINT importIndex ) {
		return module->GetImportedFunctionSourceModule( importIndex );
	}
	int asModule_BindImportedFunction( asIScriptModule* module, asUINT importIndex, asIScriptFunction* func ) {
		return module->BindImportedFunction( importIndex, func );
	}
	int asModule_UnbindImportedFunction( asIScriptModule* module, asUINT importIndex ) {
		return module->UnbindImportedFunction( importIndex );
	}
	int asModule_BindAllImportedFunctions( asIScriptModule* module ) {
		return module->BindAllImportedFunctions();
	}
	int asModule_UnbindAllImportedFunctions( asIScriptModule* module ) {
		return module->UnbindAllImportedFunctions();
	}

	// Byte code saving and loading
	int asModule_SaveByteCode( asIScriptModule* module, asBinaryStream* out, asBOOL_t stripDebugInfo ) {
		return module->SaveByteCode( new asCBinaryStream(out), static_cast<bool>( stripDebugInfo ) );
	}
	int asModule_LoadByteCode( asIScriptModule* module, asBinaryStream* in, asBOOL_t* wasDebugInfoStripped ) {
		return module->LoadByteCode( new asCBinaryStream(in), reinterpret_cast<bool*>( wasDebugInfoStripped ) );
	}

	// User data
	void* asModule_SetUserData( asIScriptModule* module, void* data, asPWORD type ) {
		return module->SetUserData( data, type );
	}
	void* asModule_GetUserData( asIScriptModule* module, asPWORD type ) {
		return module->GetUserData( type );
	}
	// endregion Interface declarations - module

	// region Interface declarations - context
	int asContext_AddRef( asIScriptContext* context ) {
		return context->AddRef();
	}
	int asContext_Release( asIScriptContext* context ) {
		return context->Release();
	}

	// Miscellaneous
	asIScriptEngine* asContext_GetEngine( asIScriptContext* context ) {
		return context->GetEngine();
	}

	// Execution
	int asContext_Prepare( asIScriptContext* context, asIScriptFunction* func ) {
		return context->Prepare( func );
	}
	int asContext_Unprepare( asIScriptContext* context ) {
		return context->Unprepare();
	}
	int asContext_Execute( asIScriptContext* context ) {
		return context->Execute();
	}
	int asContext_Abort( asIScriptContext* context ) {
		return context->Abort();
	}
	int asContext_Suspend( asIScriptContext* context ) {
		return context->Suspend();
	}
	asEContextState asContext_GetState( asIScriptContext* context ) {
		return context->GetState();
	}
	int asContext_PushState( asIScriptContext* context ) {
		return context->PushState();
	}
	int asContext_PopState( asIScriptContext* context ) {
		return context->PopState();
	}
	asBOOL_t asContext_IsNested( asIScriptContext* context, asUINT* nestCount ) {
		return static_cast<asBOOL_t>( context->IsNested( nestCount ) );
	}

	// Object pointer for calling class methods
	int asContext_SetObject( asIScriptContext* context, void* obj ) {
		return context->SetObject( obj );
	}

	// Arguments
	int asContext_SetArgByte( asIScriptContext* context, asUINT arg, asBYTE value ) {
		return context->SetArgByte( arg, value );
	}
	int asContext_SetArgWord( asIScriptContext* context, asUINT arg, asWORD value ) {
		return context->SetArgWord( arg, value );
	}
	int asContext_SetArgDWord( asIScriptContext* context, asUINT arg, asDWORD value ) {
		return context->SetArgDWord( arg, value );
	}
	int asContext_SetArgQWord( asIScriptContext* context, asUINT arg, asQWORD value ) {
		return context->SetArgQWord( arg, value );
	}
	int asContext_SetArgFloat( asIScriptContext* context, asUINT arg, float value ) {
		return context->SetArgFloat( arg, value );
	}
	int asContext_SetArgDouble( asIScriptContext* context, asUINT arg, double value ) {
		return context->SetArgDouble( arg, value );
	}
	int asContext_SetArgAddress( asIScriptContext* context, asUINT arg, void* addr ) {
		return context->SetArgAddress( arg, addr );
	}
	int asContext_SetArgObject( asIScriptContext* context, asUINT arg, void* obj ) {
		return context->SetArgObject( arg, obj );
	}
	int asContext_SetArgVarType( asIScriptContext* context, asUINT arg, void* ptr, int typeId ) {
		return context->SetArgVarType( arg, ptr, typeId );
	}
	void* asContext_GetAddressOfArg( asIScriptContext* context, asUINT arg ) {
		return context->GetAddressOfArg( arg );
	}

	// Return value
	asBYTE asContext_GetReturnByte( asIScriptContext* context ) {
		return context->GetReturnByte();
	}
	asWORD asContext_GetReturnWord( asIScriptContext* context ) {
		return context->GetReturnWord();
	}
	asDWORD asContext_GetReturnDWord( asIScriptContext* context ) {
		return context->GetReturnDWord();
	}
	asQWORD asContext_GetReturnQWord( asIScriptContext* context ) {
		return context->GetReturnQWord();
	}
	float asContext_GetReturnFloat( asIScriptContext* context ) {
		return context->GetReturnFloat();
	}
	double asContext_GetReturnDouble( asIScriptContext* context ) {
		return context->GetReturnDouble();
	}
	void* asContext_GetReturnAddress( asIScriptContext* context ) {
		return context->GetReturnAddress();
	}
	void* asContext_GetReturnObject( asIScriptContext* context ) {
		return context->GetReturnObject();
	}
	void* asContext_GetAddressOfReturnValue( asIScriptContext* context ) {
		return context->GetAddressOfReturnValue();
	}

	// Exception handling
	int asContext_SetException( asIScriptContext* context, const char* info, asBOOL_t allowCatch ) {
		return context->SetException( info, static_cast<bool>( allowCatch ) );
	}
	int asContext_GetExceptionLineNumber( asIScriptContext* context, int* column, const char** sectionName ) {
		return context->GetExceptionLineNumber( column, sectionName );
	}
	asIScriptFunction* asContext_GetExceptionFunction( asIScriptContext* context ) {
		return context->GetExceptionFunction();
	}
	const char* asContext_GetExceptionString( asIScriptContext* context ) {
		return context->GetExceptionString();
	}
	asBOOL_t asContext_WillExceptionBeCaught( asIScriptContext* context ) {
		return static_cast<asBOOL_t>( context->WillExceptionBeCaught() );
	}
	int asContext_SetExceptionCallback( asIScriptContext* context, asFUNCTION_t callback, void* obj, int callConv ) {
		return context->SetExceptionCallback( asFUNCTION( callback ), obj, callConv );
	}
	void asContext_ClearExceptionCallback( asIScriptContext* context ) {
		return context->ClearExceptionCallback();
	}

	// Debugging
	int asContext_SetLineCallback( asIScriptContext* context, asFUNCTION_t callback, void* obj, int callConv ) {
		return context->SetLineCallback( asFUNCTION( callback ), obj, callConv );
	}
	void asContext_ClearLineCallback( asIScriptContext* context ) {
		return context->ClearLineCallback();
	}
	asUINT asContext_GetCallstackSize( asIScriptContext* context ) {
		return context->GetCallstackSize();
	}
	asIScriptFunction* asContext_GetFunction( asIScriptContext* context, asUINT stackLevel ) {
		return context->GetFunction( stackLevel );
	}
	int asContext_GetLineNumber( asIScriptContext* context, asUINT stackLevel, int* column, const char** sectionName ) {
		return context->GetLineNumber( stackLevel, column, sectionName );
	}
	int asContext_GetVarCount( asIScriptContext* context, asUINT stackLevel ) {
		return context->GetVarCount( stackLevel );
	}
	int asContext_GetVar( asIScriptContext* context, asUINT varIndex, asUINT stackLevel, const char** name, int* typeId, asETypeModifiers* typeModifiers, asBOOL_t* isVarOnHeap, int* stackOffset ) {
		return context->GetVar( varIndex, stackLevel, name, typeId, typeModifiers, reinterpret_cast<bool*>( isVarOnHeap ), stackOffset );
	}
	const char* asContext_GetVarDeclaration( asIScriptContext* context, asUINT varIndex, asUINT stackLevel, asBOOL_t includeNamespace = asFALSE ) {
		return context->GetVarDeclaration( varIndex, stackLevel, includeNamespace );
	}
	void* asContext_GetAddressOfVar( asIScriptContext* context, asUINT varIndex, asUINT stackLevel, asBOOL_t dontDereference, asBOOL_t returnAddressOfUnitializedObjects ) {
		return context->GetAddressOfVar( varIndex, stackLevel, dontDereference, returnAddressOfUnitializedObjects );
	}
	asBOOL_t asContext_IsVarInScope( asIScriptContext* context, asUINT varIndex, asUINT stackLevel ) {
		return static_cast<asBOOL_t>( context->IsVarInScope( varIndex, stackLevel ) );
	}
	int asContext_GetThisTypeId( asIScriptContext* context, asUINT stackLevel ) {
		return context->GetThisTypeId( stackLevel );
	}
	void* asContext_GetThisPointer( asIScriptContext* context, asUINT stackLevel ) {
		return context->GetThisPointer( stackLevel );
	}
	asIScriptFunction* asContext_GetSystemFunction( asIScriptContext* context ) {
		return context->GetSystemFunction();
	}

	// User data
	void* asContext_SetUserData( asIScriptContext* context, void* data, asPWORD type ) {
		return context->SetUserData( data, type );
	}
	void* asContext_GetUserData( asIScriptContext* context, asPWORD type ) {
		return context->GetUserData( type );
	}

	// Serialization
	int asContext_StartDeserialization( asIScriptContext* context ) {
		return context->StartDeserialization();
	}
	int asContext_FinishDeserialization( asIScriptContext* context ) {
		return context->FinishDeserialization();
	}
	int asContext_PushFunction( asIScriptContext* context, asIScriptFunction* func, void* object ) {
		return context->PushFunction( func, object );
	}
	int asContext_GetStateRegisters( asIScriptContext* context, asUINT stackLevel, asIScriptFunction** callingSystemFunction, asIScriptFunction** initialFunction, asDWORD* origStackPointer, asDWORD* argumentsSize, asQWORD* valueRegister, void** objectRegister, asITypeInfo** objectTypeRegister ) {
		return context->GetStateRegisters( stackLevel, callingSystemFunction, initialFunction, origStackPointer, argumentsSize, valueRegister, objectRegister, objectTypeRegister );
	}
	int asContext_GetCallStateRegisters( asIScriptContext* context, asUINT stackLevel, asDWORD* stackFramePointer, asIScriptFunction** currentFunction, asDWORD* programPointer, asDWORD* stackPointer, asDWORD* stackIndex ) {
		return context->GetCallStateRegisters( stackLevel, stackFramePointer, currentFunction, programPointer, stackPointer, stackIndex );
	}
	int asContext_SetStateRegisters( asIScriptContext* context, asUINT stackLevel, asIScriptFunction* callingSystemFunction, asIScriptFunction* initialFunction, asDWORD origStackPointer, asDWORD argumentsSize, asQWORD valueRegister, void* objectRegister, asITypeInfo* objectTypeRegister ) {
		return context->SetStateRegisters( stackLevel, callingSystemFunction, initialFunction, origStackPointer, argumentsSize, valueRegister, objectRegister, objectTypeRegister );
	}
	int asContext_SetCallStateRegisters( asIScriptContext* context, asUINT stackLevel, asDWORD stackFramePointer, asIScriptFunction* currentFunction, asDWORD programPointer, asDWORD stackPointer, asDWORD stackIndex ) {
		return context->SetCallStateRegisters( stackLevel, stackFramePointer, currentFunction, programPointer, stackPointer, stackIndex );
	}
	int asContext_GetArgsOnStackCount( asIScriptContext* context, asUINT stackLevel ) {
		return context->GetArgsOnStackCount( stackLevel );
	}
	int asContext_GetArgOnStack( asIScriptContext* context, asUINT stackLevel, asUINT arg, int* typeId, asUINT* flags, void** address ) {
		return context->GetArgOnStack( stackLevel, arg, typeId, flags, address );
	}
	// endregion Interface declarations - context

	// region Interface declarations - generic
	// Miscellaneous
	asIScriptEngine* asGeneric_GetEngine( asIScriptGeneric* generic ) {
		return generic->GetEngine();
	}
	asIScriptFunction* asGeneric_GetFunction( asIScriptGeneric* generic ) {
		return generic->GetFunction();
	}
	void* asGeneric_GetAuxiliary( asIScriptGeneric* generic ) {
		return generic->GetAuxiliary();
	}

	// Object
	void* asGeneric_GetObject( asIScriptGeneric* generic ) {
		return generic->GetObject();
	}
	int asGeneric_GetObjectTypeId( asIScriptGeneric* generic ) {
		return generic->GetObjectTypeId();
	}

	// Arguments
	int asGeneric_GetArgCount( asIScriptGeneric* generic ) {
		return generic->GetArgCount();
	}
	int asGeneric_GetArgTypeId( asIScriptGeneric* generic, asUINT arg, asDWORD* flags ) {
		return generic->GetArgTypeId( arg, flags );
	}
	asBYTE asGeneric_GetArgByte( asIScriptGeneric* generic, asUINT arg ) {
		return generic->GetArgByte( arg );
	}
	asWORD asGeneric_GetArgWord( asIScriptGeneric* generic, asUINT arg ) {
		return generic->GetArgWord( arg );
	}
	asDWORD asGeneric_GetArgDWord( asIScriptGeneric* generic, asUINT arg ) {
		return generic->GetArgDWord( arg );
	}
	asQWORD asGeneric_GetArgQWord( asIScriptGeneric* generic, asUINT arg ) {
		return generic->GetArgQWord( arg );
	}
	float asGeneric_GetArgFloat( asIScriptGeneric* generic, asUINT arg ) {
		return generic->GetArgFloat( arg );
	}
	double asGeneric_GetArgDouble( asIScriptGeneric* generic, asUINT arg ) {
		return generic->GetArgDouble( arg );
	}
	void* asGeneric_GetArgAddress( asIScriptGeneric* generic, asUINT arg ) {
		return generic->GetArgAddress( arg );
	}
	void* asGeneric_GetArgObject( asIScriptGeneric* generic, asUINT arg ) {
		return generic->GetArgObject( arg );
	}
	void* asGeneric_GetAddressOfArg( asIScriptGeneric* generic, asUINT arg ) {
		return generic->GetAddressOfArg( arg );
	}

	// Return value
	int asGeneric_GetReturnTypeId( asIScriptGeneric* generic, asDWORD* flags ) {
		return generic->GetReturnTypeId( flags );
	}
	int asGeneric_SetReturnByte( asIScriptGeneric* generic, asBYTE val ) {
		return generic->SetReturnByte( val );
	}
	int asGeneric_SetReturnWord( asIScriptGeneric* generic, asWORD val ) {
		return generic->SetReturnWord( val );
	}
	int asGeneric_SetReturnDWord( asIScriptGeneric* generic, asDWORD val ) {
		return generic->SetReturnDWord( val );
	}
	int asGeneric_SetReturnQWord( asIScriptGeneric* generic, asQWORD val ) {
		return generic->SetReturnQWord( val );
	}
	int asGeneric_SetReturnFloat( asIScriptGeneric* generic, float val ) {
		return generic->SetReturnFloat( val );
	}
	int asGeneric_SetReturnDouble( asIScriptGeneric* generic, double val ) {
		return generic->SetReturnDouble( val );
	}
	int asGeneric_SetReturnAddress( asIScriptGeneric* generic, void* addr ) {
		return generic->SetReturnAddress( addr );
	}
	int asGeneric_SetReturnObject( asIScriptGeneric* generic, void* obj ) {
		return generic->SetReturnObject( obj );
	}
	void* asGeneric_GetAddressOfReturnLocation( asIScriptGeneric* generic ) {
		return generic->GetAddressOfReturnLocation();
	}
	// endregion Interface declarations - generic

	// region Interface declarations - object
	// Memory management
	int asObject_AddRef( asIScriptObject* object ) {
		return object->AddRef();
	}
	int asObject_Release( asIScriptObject* object ) {
		return object->Release();
	}
	asILockableSharedBool* asObject_GetWeakRefFlag( asIScriptObject* object ) {
		return object->GetWeakRefFlag();
	}

	// Type info
	int asObject_GetTypeId( asIScriptObject* object ) {
		return object->GetTypeId();
	}
	asITypeInfo* asObject_GetObjectType( asIScriptObject* object ) {
		return object->GetObjectType();
	}

	// Class properties
	asUINT asObject_GetPropertyCount( asIScriptObject* object ) {
		return object->GetPropertyCount();
	}
	int asObject_GetPropertyTypeId( asIScriptObject* object, asUINT prop ) {
		return object->GetPropertyTypeId( prop );
	}
	const char* asObject_GetPropertyName( asIScriptObject* object, asUINT prop ) {
		return object->GetPropertyName( prop );
	}
	void* asObject_GetAddressOfProperty( asIScriptObject* object, asUINT prop ) {
		return object->GetAddressOfProperty( prop );
	}

	// Miscellaneous
	asIScriptEngine* asObject_GetEngine( asIScriptObject* object ) {
		return object->GetEngine();
	}
	int asObject_CopyFrom( asIScriptObject* object, const asIScriptObject* other ) {
		return object->CopyFrom( other );
	}

	// User data
	void* asObject_SetUserData( asIScriptObject* object, void* data, asPWORD type ) {
		return object->SetUserData( data, type );
	}
	void* asObject_GetUserData( asIScriptObject* object, asPWORD type ) {
		return object->GetUserData( type );
	}
	// endregion Interface declarations - object

	// region Interface declarations - type info
	// Miscellaneous
	asIScriptEngine* asTypeInfo_GetEngine( asITypeInfo* info ) {
		return info->GetEngine();
	}
	const char* asTypeInfo_GetConfigGroup( asITypeInfo* info ) {
		return info->GetConfigGroup();
	}
	asDWORD asTypeInfo_GetAccessMask( asITypeInfo* info ) {
		return info->GetAccessMask();
	}
	asIScriptModule* asTypeInfo_GetModule( asITypeInfo* info ) {
		return info->GetModule();
	}

	// Memory management
	int asTypeInfo_AddRef( asITypeInfo* info ) {
		return info->AddRef();
	}
	int asTypeInfo_Release( asITypeInfo* info ) {
		return info->Release();
	}

	// Type info
	const char* asTypeInfo_GetName( asITypeInfo* info ) {
		return info->GetName();
	}
	const char* asTypeInfo_GetNamespace( asITypeInfo* info ) {
		return info->GetNamespace();
	}
	asITypeInfo* asTypeInfo_GetBaseType( asITypeInfo* info ) {
		return info->GetBaseType();
	}
	asBOOL_t asTypeInfo_DerivesFrom( asITypeInfo* info, const asITypeInfo* objType ) {
		return static_cast<asBOOL_t>( info->DerivesFrom( objType ) );
	}
	asDWORD asTypeInfo_GetFlags( asITypeInfo* info ) {
		return info->GetFlags();
	}
	asUINT asTypeInfo_GetSize( asITypeInfo* info ) {
		return info->GetSize();
	}
	int asTypeInfo_GetTypeId( asITypeInfo* info ) {
		return info->GetTypeId();
	}
	int asTypeInfo_GetSubTypeId( asITypeInfo* info, asUINT subTypeIndex ) {
		return info->GetSubTypeId( subTypeIndex );
	}
	asITypeInfo* asTypeInfo_GetSubType( asITypeInfo* info, asUINT subTypeIndex ) {
		return info->GetSubType( subTypeIndex );
	}
	asUINT asTypeInfo_GetSubTypeCount( asITypeInfo* info ) {
		return info->GetSubTypeCount();
	}

	// Interfaces
	asUINT asTypeInfo_GetInterfaceCount( asITypeInfo* info ) {
		return info->GetInterfaceCount();
	}
	asITypeInfo* asTypeInfo_GetInterface( asITypeInfo* info, asUINT index ) {
		return info->GetInterface( index );
	}
	asBOOL_t asTypeInfo_Implements( asITypeInfo* info, const asITypeInfo* objType ) {
		return static_cast<asBOOL_t>( info->Implements( objType ) );
	}

	// Factories
	asUINT asTypeInfo_GetFactoryCount( asITypeInfo* info ) {
		return info->GetFactoryCount();
	}
	asIScriptFunction* asTypeInfo_GetFactoryByIndex( asITypeInfo* info, asUINT index ) {
		return info->GetFactoryByIndex( index );
	}
	asIScriptFunction* asTypeInfo_GetFactoryByDecl( asITypeInfo* info, const char* decl ) {
		return info->GetFactoryByDecl( decl );
	}

	// Methods
	asUINT asTypeInfo_GetMethodCount( asITypeInfo* info ) {
		return info->GetMethodCount();
	}
	asIScriptFunction* asTypeInfo_GetMethodByIndex( asITypeInfo* info, asUINT index, asBOOL_t getVirtual ) {
		return info->GetMethodByIndex( index, static_cast<bool>( getVirtual ) );
	}
	asIScriptFunction* asTypeInfo_GetMethodByName( asITypeInfo* info, const char* name, asBOOL_t getVirtual ) {
		return info->GetMethodByName( name, static_cast<bool>( getVirtual ) );
	}
	asIScriptFunction* asTypeInfo_GetMethodByDecl( asITypeInfo* info, const char* decl, asBOOL_t getVirtual ) {
		return info->GetMethodByDecl( decl, static_cast<bool>( getVirtual ) );
	}

	// Properties
	asUINT asTypeInfo_GetPropertyCount( asITypeInfo* info ) {
		return info->GetPropertyCount();
	}
	int asTypeInfo_GetProperty( asITypeInfo* info, asUINT index, const char** name, int* typeId, asBOOL_t* isPrivate, asBOOL_t* isProtected, int* offset, asBOOL_t* isReference, asDWORD* accessMask, int* compositeOffset, asBOOL_t* isCompositeIndirect ) {
		return info->GetProperty( index, name, typeId, reinterpret_cast<bool*>( isPrivate ), reinterpret_cast<bool*>( isProtected ), offset, reinterpret_cast<bool*>( isReference ), accessMask, compositeOffset, reinterpret_cast<bool*>( isCompositeIndirect ) );
	}
	const char* asTypeInfo_GetPropertyDeclaration( asITypeInfo* info, asUINT index, asBOOL_t includeNamespace ) {
		return info->GetPropertyDeclaration( index, static_cast<bool>( includeNamespace ) );
	}

	// Behaviours
	asUINT asTypeInfo_GetBehaviourCount( asITypeInfo* info ) {
		return info->GetBehaviourCount();
	}
	asIScriptFunction* asTypeInfo_GetBehaviourByIndex( asITypeInfo* info, asUINT index, asEBehaviours* outBehaviour ) {
		return info->GetBehaviourByIndex( index, outBehaviour );
	}

	// Child types
	asUINT asTypeInfo_GetChildFuncdefCount( asITypeInfo* info ) {
		return info->GetChildFuncdefCount();
	}
	asITypeInfo* asTypeInfo_GetChildFuncdef( asITypeInfo* info, asUINT index ) {
		return info->GetChildFuncdef( index );
	}
	asITypeInfo* asTypeInfo_GetParentType( asITypeInfo* info ) {
		return info->GetParentType();
	}

	// Enums
	asUINT asTypeInfo_GetEnumValueCount( asITypeInfo* info ) {
		return info->GetEnumValueCount();
	}
	const char* asTypeInfo_GetEnumValueByIndex( asITypeInfo* info, asUINT index, int* outValue ) {
		return info->GetEnumValueByIndex( index, outValue );
	}

	// Typedef
	int asTypeInfo_GetTypedefTypeId( asITypeInfo* info ) {
		return info->GetTypedefTypeId();
	}

	// Funcdef
	asIScriptFunction* asTypeInfo_GetFuncdefSignature( asITypeInfo* info ) {
		return info->GetFuncdefSignature();
	}

	// User data
	void* asTypeInfo_SetUserData( asITypeInfo* info, void* data, asPWORD type ) {
		return info->SetUserData( data, type );
	}
	void* asTypeInfo_GetUserData( asITypeInfo* info, asPWORD type ) {
		return info->GetUserData( type );
	}
	// endregion Interface declarations - type info

	// region Interface declarations - function
	asIScriptEngine* asFunction_GetEngine( asIScriptFunction* function ) {
		return function->GetEngine();
	}

	// Memory management
	int asFunction_AddRef( asIScriptFunction* function ) {
		return function->AddRef();
	}
	int asFunction_Release( asIScriptFunction* function ) {
		return function->Release();
	}

	// Miscellaneous
	int asFunction_GetId( asIScriptFunction* function ) {
		return function->GetId();
	}
	asEFuncType asFunction_GetFuncType( asIScriptFunction* function ) {
		return function->GetFuncType();
	}
	const char* asFunction_GetModuleName( asIScriptFunction* function ) {
		return function->GetModuleName();
	}
	asIScriptModule* asFunction_GetModule( asIScriptFunction* function ) {
		return function->GetModule();
	}
	const char* asFunction_GetScriptSectionName( asIScriptFunction* function ) {
		return function->GetScriptSectionName();
	}
	const char* asFunction_GetConfigGroup( asIScriptFunction* function ) {
		return function->GetConfigGroup();
	}
	asDWORD asFunction_GetAccessMask( asIScriptFunction* function ) {
		return function->GetAccessMask();
	}
	void* asFunction_GetAuxiliary( asIScriptFunction* function ) {
		return function->GetAuxiliary();
	}

	// Function signature
	asITypeInfo* asFunction_GetObjectType( asIScriptFunction* function ) {
		return function->GetObjectType();
	}
	const char* asFunction_GetObjectName( asIScriptFunction* function ) {
		return function->GetObjectName();
	}
	const char* asFunction_GetName( asIScriptFunction* function ) {
		return function->GetName();
	}
	const char* asFunction_GetNamespace( asIScriptFunction* function ) {
		return function->GetNamespace();
	}
	const char* asFunction_GetDeclaration( asIScriptFunction* function, asBOOL_t includeObjectName, asBOOL_t includeNamespace, asBOOL_t includeParamNames ) {
		return function->GetDeclaration( includeObjectName, includeNamespace, includeParamNames );
	}
	asBOOL_t asFunction_IsReadOnly( asIScriptFunction* function ) {
		return static_cast<asBOOL_t>( function->IsReadOnly() );
	}
	asBOOL_t asFunction_IsPrivate( asIScriptFunction* function ) {
		return static_cast<asBOOL_t>( function->IsPrivate() );
	}
	asBOOL_t asFunction_IsProtected( asIScriptFunction* function ) {
		return static_cast<asBOOL_t>( function->IsProtected() );
	}
	asBOOL_t asFunction_IsFinal( asIScriptFunction* function ) {
		return static_cast<asBOOL_t>( function->IsFinal() );
	}
	asBOOL_t asFunction_IsOverride( asIScriptFunction* function ) {
		return static_cast<asBOOL_t>( function->IsOverride() );
	}
	asBOOL_t asFunction_IsShared( asIScriptFunction* function ) {
		return static_cast<asBOOL_t>( function->IsShared() );
	}
	asBOOL_t asFunction_IsExplicit( asIScriptFunction* function ) {
		return static_cast<asBOOL_t>( function->IsExplicit() );
	}
	asBOOL_t asFunction_IsProperty( asIScriptFunction* function ) {
		return static_cast<asBOOL_t>( function->IsProperty() );
	}
	asUINT asFunction_GetParamCount( asIScriptFunction* function ) {
		return function->GetParamCount();
	}
	int asFunction_GetParam( asIScriptFunction* function, asUINT index, int* typeId, asDWORD* flags, const char** name, const char** defaultArg ) {
		return function->GetParam( index, typeId, flags, name, defaultArg );
	}
	int asFunction_GetReturnTypeId( asIScriptFunction* function, asDWORD* flags ) {
		return function->GetReturnTypeId( flags );
	}

	// Type id for function pointers
	int asFunction_GetTypeId( asIScriptFunction* function ) {
		return function->GetTypeId();
	}
	asBOOL_t asFunction_IsCompatibleWithTypeId( asIScriptFunction* function, int typeId ) {
		return static_cast<asBOOL_t>( function->IsCompatibleWithTypeId( typeId ) );
	}

	// Delegates
	void* asFunction_GetDelegateObject( asIScriptFunction* function ) {
		return function->GetDelegateObject();
	}
	asITypeInfo* asFunction_GetDelegateObjectType( asIScriptFunction* function ) {
		return function->GetDelegateObjectType();
	}
	asIScriptFunction* asFunction_GetDelegateFunction( asIScriptFunction* function ) {
		return function->GetDelegateFunction();
	}

	// Debug information
	asUINT asFunction_GetVarCount( asIScriptFunction* function ) {
		return function->GetVarCount();
	}
	int asFunction_GetVar( asIScriptFunction* function, asUINT index, const char** name, int* typeId ) {
		return function->GetVar( index, name, typeId );
	}
	const char* asFunction_GetVarDecl( asIScriptFunction* function, asUINT index, asBOOL_t includeNamespace ) {
		return function->GetVarDecl( index, includeNamespace );
	}
	int asFunction_FindNextLineWithCode( asIScriptFunction* function, int line ) {
		return function->FindNextLineWithCode( line );
	}

	// For JIT compilation
	asDWORD* asFunction_GetByteCode( asIScriptFunction* function, asUINT* length ) {
		return function->GetByteCode( length );
	}

	// User data
	void* asFunction_SetUserData( asIScriptFunction* function, void* userData, asPWORD type ) {
		return function->SetUserData( userData, type );
	}
	void* asFunction_GetUserData( asIScriptFunction* function, asPWORD type ) {
		return function->GetUserData( type );
	}
	// endregion Interface declarations - function

	// region Interface declarations - lockable shared bool
	// Memory management
	int asLockableSharedBool_AddRef( asILockableSharedBool* lockable ) {
		return lockable->AddRef();
	}
	int asLockableSharedBool_Release( asILockableSharedBool* lockable ) {
		return lockable->Release();
	}

	// Value
	asBOOL_t asLockableSharedBool_Get( asILockableSharedBool* lockable ) {
		return static_cast<asBOOL_t>( lockable->Get() );
	}
	void asLockableSharedBool_Set( asILockableSharedBool* lockable, asBOOL_t val ) {
		return lockable->Set( val );
	}

	// Thread management
	void asLockableSharedBool_Lock( asILockableSharedBool* lockable ) {
		return lockable->Lock();
	}
	void asLockableSharedBool_Unlock( asILockableSharedBool* lockable ) {
		return lockable->Unlock();
	}
	// endregion Interface declarations - lockable shared bool
}
