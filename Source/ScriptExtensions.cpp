#include "Script.h"

static void CScriptArray_InsertFirst( CScriptArray* arr, void* value )
{
    arr->InsertAt( 0, value );
}

static void CScriptArray_RemoveFirst( CScriptArray* arr )
{
    arr->RemoveAt( 0 );
}

static void CScriptArray_Grow( CScriptArray* arr, asUINT numElements )
{
    if( numElements == 0 )
        return;

    arr->Resize( arr->GetSize() + numElements );
}

static void CScriptArray_Reduce( CScriptArray* arr, asUINT numElements )
{
    if( numElements == 0 )
        return;

    asUINT size = arr->GetSize();
    if( numElements > size )
    {
        asIScriptContext* ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException( "Array size is less than reduce count" );
        return;
    }
    arr->Resize( size - numElements );
}

static void* CScriptArray_First( CScriptArray* arr )
{
    return arr->At( 0 );
}

static void* CScriptArray_Last( CScriptArray* arr )
{
    return arr->At( arr->GetSize() - 1 );
}

static void CScriptArray_Clear( CScriptArray* arr )
{
    if( arr->GetSize() > 0 )
        arr->Resize( 0 );
}

static bool CScriptArray_Exists( const CScriptArray* arr, void* value )
{
    return arr->Find( 0, value ) != -1;
}

static CScriptArray* CScriptArray_Clone( asITypeInfo* ti, const CScriptArray** other )
{
    if( !*other )
    {
        asIScriptContext* ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException( "Array is null" );
        return nullptr;
    }

    CScriptArray* clone = CScriptArray::Create( ti );
    *clone = **other;
    return clone;
}

static void CScriptArray_Set( CScriptArray* arr, const CScriptArray** other )
{
    if( !*other )
    {
        asIScriptContext* ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException( "Array is null" );
        return;
    }

    *arr = **other;
}

static void CScriptArray_InsertArrAt( CScriptArray* arr, uint index, const CScriptArray** other )
{
    if( !*other )
    {
        asIScriptContext* ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException( "Array is null" );
        return;
    }

    arr->InsertAt( index, **other );
}

static void CScriptArray_InsertArrFirst( CScriptArray* arr, const CScriptArray** other )
{
    if( !*other )
    {
        asIScriptContext* ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException( "Array is null" );
        return;
    }

    arr->InsertAt( 0, **other );
}

static void CScriptArray_InsertArrLast( CScriptArray* arr, const CScriptArray** other )
{
    if( !*other )
    {
        asIScriptContext* ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException( "Array is null" );
        return;
    }

    arr->InsertAt( arr->GetSize() - 1, **other );
}

static bool CScriptArray_Equals( CScriptArray* arr, const CScriptArray** other )
{
    if( !*other )
    {
        asIScriptContext* ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException( "Array is null" );
        return false;
    }

    return *arr == **other;
}

void Script::RegisterScriptArrayExtensions( asIScriptEngine* engine )
{
    int r = engine->RegisterObjectMethod( "array<T>", "void insertFirst(const T&in)", asFUNCTION( CScriptArray_InsertFirst ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "void removeFirst()", asFUNCTION( CScriptArray_RemoveFirst ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "void grow(uint)", asFUNCTION( CScriptArray_Grow ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "void reduce(uint)", asFUNCTION( CScriptArray_Reduce ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "T& first()", asFUNCTION( CScriptArray_First ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "const T& first() const", asFUNCTION( CScriptArray_First ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "T& last()", asFUNCTION( CScriptArray_Last ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "const T& last() const", asFUNCTION( CScriptArray_Last ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "void clear()", asFUNCTION( CScriptArray_Clear ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "bool exists(const T&in) const", asFUNCTION( CScriptArray_Exists ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectBehaviour( "array<T>", asBEHAVE_FACTORY, "array<T>@ f(int& in, const array<T>&in)", asFUNCTION( CScriptArray_Clone ), asCALL_CDECL );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "void set(const array<T>&in)", asFUNCTION( CScriptArray_Set ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "void insertAt(uint, const array<T>&in)", asFUNCTION( CScriptArray_InsertArrAt ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "void insertFirst(const array<T>&in)", asFUNCTION( CScriptArray_InsertArrFirst ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "void insertLast(const array<T>&in)", asFUNCTION( CScriptArray_InsertArrFirst ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "array<T>", "bool equals(const array<T>&in)", asFUNCTION( CScriptArray_Equals ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
}

static CScriptDict* ScriptDict_Clone( asITypeInfo* ti, const CScriptDict** other )
{
    CScriptDict* clone = CScriptDict::Create( ti );
    if( *other )
        *clone = **other;
    return clone;
}

static bool ScriptDict_Equals( CScriptDict* dict, const CScriptDict** other )
{
    if( !*other )
    {
        asIScriptContext* ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException( "Dict is null" );
        return false;
    }

    return *dict == **other;
}

void Script::RegisterScriptDictExtensions( asIScriptEngine* engine )
{
    int r = engine->RegisterObjectBehaviour( "dict<T1,T2>", asBEHAVE_FACTORY, "dict<T1,T2>@ f(int& in, const dict<T1,T2>&in)", asFUNCTION( ScriptDict_Clone ), asCALL_CDECL );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "dict<T1,T2>", "bool equals(const dict<T1,T2>&in)", asFUNCTION( ScriptDict_Equals ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
}

static bool IndexUTF8ToRaw( const string& str, int& index, uint* length = nullptr, uint offset = 0 )
{
    if( index < 0 )
    {
        index = (int) Str::LengthUTF8( str.c_str() ) + index;
        if( index < 0 )
        {
            index = 0;
            if( length )
            {
                if( !str.empty() )
                    Str::DecodeUTF8( str.c_str(), length );
                else
                    *length = 0;
            }
            return false;
        }
    }

    const char* begin = str.c_str() + offset;
    const char* s = begin;
    while( *s )
    {
        uint ch_length;
        Str::DecodeUTF8( s, &ch_length );
        if( index > 0 )
        {
            s += ch_length;
            index--;
        }
        else
        {
            index = (uint) ( s - begin );
            if( length )
                *length = ch_length;
            return true;
        }
    }
    index = (uint) ( s - begin );
    if( length )
        *length = 0;
    return false;
}

static int IndexRawToUTF8( const string& str, int index )
{
    int         result = 0;
    const char* s = str.c_str();
    while( index > 0 && *s )
    {
        uint ch_length;
        Str::DecodeUTF8( s, &ch_length );
        s += ch_length;
        index -= ch_length;
        result++;
    }
    return result;
}

static void ScriptString_Clear( string& str )
{
    str.clear();
}

static string ScriptString_SubString( const string& str, int start, int count )
{
    if( !IndexUTF8ToRaw( str, start ) )
        return "";
    if( count >= 0 )
        IndexUTF8ToRaw( str, count, NULL, start );
    return str.substr( start, count >= 0 ? count : std::string::npos );
}

static int ScriptString_FindFirst( const string& str, const string& sub, int start )
{
    if( !IndexUTF8ToRaw( str, start ) )
        return -1;
    int pos = (int) str.find( sub, start );
    return pos != -1 ? IndexRawToUTF8( str, pos ) : -1;
}

static int ScriptString_FindLast( const string& str, const string& sub, int start )
{
    if( !IndexUTF8ToRaw( str, start ) )
        return -1;
    int pos = (int) str.rfind( sub );
    return pos != -1 && pos >= start ? IndexRawToUTF8( str, pos ) : -1;
}

static int ScriptString_FindFirstOf( const string& str, const string& chars, int start )
{
    if( !IndexUTF8ToRaw( str, start ) )
        return -1;
    int pos = (int) str.find_first_of( chars, start );
    return pos != -1 ? IndexRawToUTF8( str, pos ) : -1;
}

static int ScriptString_FindFirstNotOf( const string& str, const string& chars, int start )
{
    if( !IndexUTF8ToRaw( str, start ) )
        return -1;
    int pos =  (int) str.find_first_not_of( chars, start );
    return pos != -1 ? IndexRawToUTF8( str, pos ) : -1;
}

static int ScriptString_FindLastOf( const string& str, const string& chars, int start )
{
    if( !IndexUTF8ToRaw( str, start ) )
        return -1;
    int pos = (int) str.find_last_of( chars );
    return pos != -1 && pos >= start ? IndexRawToUTF8( str, pos ) : -1;
}

static int ScriptString_FindLastNotOf( const string& str, const string& chars, int start )
{
    if( !IndexUTF8ToRaw( str, start ) )
        return -1;
    int pos = (int) str.find_last_not_of( chars, start );
    return pos != -1 && pos >= start ? IndexRawToUTF8( str, pos ) : -1;
}

static string ScriptString_GetAt( const string& str, int i )
{
    uint length;
    if( !IndexUTF8ToRaw( str, i, &length ) )
    {
        // Set a script exception
        asIScriptContext* ctx = asGetActiveContext();
        ctx->SetException( "Out of range" );

        // Return a null pointer
        return 0;
    }

    return string( str.c_str() + i, length );
}

static void ScriptString_SetAt( string& str, int i, string& value )
{
    uint length;
    if( !IndexUTF8ToRaw( str, i, &length ) )
    {
        // Set a script exception
        asIScriptContext* ctx = asGetActiveContext();
        ctx->SetException( "Out of range" );
        return;
    }

    if( length )
        str.erase( i, length );
    if( value.length() )
        str.insert( i, value.c_str() );
}

static uint ScriptString_Length( const string& str )
{
    return Str::LengthUTF8( str.c_str() );
}

static uint ScriptString_RawLength( const string& str )
{
    return (uint) str.length();
}

static void ScriptString_RawResize( string& str, uint length )
{
    str.resize( length );
}

static uchar ScriptString_RawGet( const string& str, uint index )
{
    return index < (uint) str.length() ? str[ index ] : 0;
}

static void ScriptString_RawSet( string& str, uint index, uchar value )
{
    if( index < (uint) str.length() )
        str[ index ] = (char) value;
}

static int ScriptString_ToInt( const string& str, int defaultValue )
{
    const char* p = str.c_str();
    while( *p == ' ' || *p == '\t' )
        ++p;

    char* end_str = NULL;
    int   result;
    if( p[ 0 ] && p[ 0 ] == '0' && ( p[ 1 ] == 'x' || p[ 1 ] == 'X' ) )
        result = (int) strtol( p + 2, &end_str, 16 );
    else
        result = (int) strtol( p, &end_str, 10 );

    if( !end_str || end_str == p )
        return defaultValue;

    while( *end_str == ' ' || *end_str == '\t' )
        ++end_str;
    if( *end_str )
        return defaultValue;

    return result;
}

static float ScriptString_ToFloat( const string& str, float defaultValue )
{
    const char* p = str.c_str();
    while( *p == ' ' || *p == '\t' )
        ++p;

    char* end_str = NULL;
    float result = (float) strtod( p, &end_str );

    if( !end_str || end_str == p )
        return defaultValue;

    while( *end_str == ' ' || *end_str == '\t' )
        ++end_str;
    if( *end_str )
        return defaultValue;

    return result;
}

static bool ScriptString_StartsWith( const string& str, const string& other )
{
    if( str.length() < other.length() )
        return false;
    return str.compare( 0, other.length(), other ) == 0;
}

static bool ScriptString_EndsWith( const string& str, const string& other )
{
    if( str.length() < other.length() )
        return false;
    return str.compare( str.length() - other.length(), other.length(), other ) == 0;
}

static string ScriptString_Lower( const string& str )
{
    string result = str;
    Str::LowerUTF8( (char*) result.c_str() );
    return result;
}

static string ScriptString_Upper( const string& str )
{
    string result = str;
    Str::UpperUTF8( (char*) result.c_str() );
    return result;
}

static CScriptArray* ScriptString_Split( const string& delim, const string& str )
{
    CScriptArray* array = Script::CreateArray( "string[]" );

    // Find the existence of the delimiter in the input string
    int pos = 0, prev = 0, count = 0;
    while( ( pos = (int) str.find( delim, prev ) ) != (int) string::npos )
    {
        // Add the part to the array
        array->Resize( array->GetSize() + 1 );
        ( (string*) array->At( count ) )->assign( &str[ prev ], pos - prev );

        // Find the next part
        count++;
        prev = pos + (int) delim.length();
    }

    // Add the remaining part
    array->Resize( array->GetSize() + 1 );
    ( (string*) array->At( count ) )->assign( &str[ prev ] );

    return array;
}

static string ScriptString_Join( const CScriptArray** parray, const string& delim )
{
    const CScriptArray* array = *parray;
    if( !array )
    {
        asIScriptContext* ctx = asGetActiveContext();
        if( ctx )
            ctx->SetException( "Array is null" );
        return "";
    }

    // Create the new string
    string str = "";
    if( array->GetSize() )
    {
        int n;
        for( n = 0; n < (int) array->GetSize() - 1; n++ )
        {
            str += *(string*) array->At( n );
            str += delim;
        }

        // Add the last part
        str += *(string*) array->At( n );
    }

    return str;
}

void Script::RegisterScriptStdStringExtensions( asIScriptEngine* engine )
{
    int r = engine->RegisterObjectMethod( "string", "void clear()", asFUNCTION( ScriptString_Clear ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "uint length() const", asFUNCTION( ScriptString_Length ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "uint rawLength() const", asFUNCTION( ScriptString_RawLength ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "void rawResize(uint)", asFUNCTION( ScriptString_RawResize ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "uint8 rawGet(uint) const", asFUNCTION( ScriptString_RawGet ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "void rawSet(uint, uint8)", asFUNCTION( ScriptString_RawSet ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );

    r = engine->RegisterObjectMethod( "string", "string substr(uint start = 0, int count = -1) const", asFUNCTION( ScriptString_SubString ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "int findFirst(const string &in, uint start = 0) const", asFUNCTION( ScriptString_FindFirst ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "int findFirstOf(const string &in, uint start = 0) const", asFUNCTION( ScriptString_FindFirstOf ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "int findFirstNotOf(const string &in, uint start = 0) const", asFUNCTION( ScriptString_FindFirstNotOf ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "int findLast(const string &in, int start = -1) const", asFUNCTION( ScriptString_FindLast ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "int findLastOf(const string &in, int start = -1) const", asFUNCTION( ScriptString_FindLastOf ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "int findLastNotOf(const string &in, int start = -1) const", asFUNCTION( ScriptString_FindLastNotOf ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );

    // Register the index operator, both as a mutator and as an inspector
    r = engine->RegisterObjectMethod( "string", "string get_opIndex(int) const", asFUNCTION( ScriptString_GetAt ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "void set_opIndex(int, const string &in)", asFUNCTION( ScriptString_SetAt ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );

    // Conversion methods
    r = engine->RegisterObjectMethod( "string", "int toInt(int defaultValue = 0) const", asFUNCTION( ScriptString_ToInt ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "float toFloat(float defaultValue = 0) const", asFUNCTION( ScriptString_ToFloat ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );

    // Find methods
    r = engine->RegisterObjectMethod( "string", "bool startsWith(const string &in) const", asFUNCTION( ScriptString_StartsWith ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "bool endsWith(const string &in) const", asFUNCTION( ScriptString_EndsWith ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );

    r = engine->RegisterObjectMethod( "string", "string lower() const", asFUNCTION( ScriptString_Lower ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterObjectMethod( "string", "string upper() const", asFUNCTION( ScriptString_Upper ), asCALL_CDECL_OBJFIRST );
    RUNTIME_ASSERT( r >= 0 );

    r = engine->RegisterObjectMethod( "string", "array<string>@ split(const string &in) const", asFUNCTION( ScriptString_Split ), asCALL_CDECL_OBJLAST );
    RUNTIME_ASSERT( r >= 0 );
    r = engine->RegisterGlobalFunction( "string join(const array<string>@ &in, const string &in)", asFUNCTION( ScriptString_Join ), asCALL_CDECL );
    RUNTIME_ASSERT( r >= 0 );
}