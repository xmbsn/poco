//
// TestStatementImpl.h
//
// $Id: //poco/Main/Data/testsuite/src/TestStatementImpl.h#2 $
//
// Definition of the TestStatementImpl class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Data_Test_TestStatementImpl_INCLUDED
#define Data_Test_TestStatementImpl_INCLUDED


#include "Poco/Data/StatementImpl.h"
#include "Poco/Data/MetaColumn.h"
#include "Poco/SharedPtr.h"
#include "Binder.h"
#include "Extractor.h"
#include "Preparator.h"


namespace Poco {
namespace Data {
namespace Test {


class SessionImpl;


class TestStatementImpl: public Poco::Data::StatementImpl
	/// A no-op implementation of TestStatementImpl for testing.
{
public:
	TestStatementImpl(SessionImpl& rSession);
		/// Creates the TestStatementImpl.

	~TestStatementImpl();
		/// Destroys the TestStatementImpl.

protected:
	std::size_t columnsReturned() const;
		/// Returns number of columns returned by query. 
	
	std::size_t affectedRowCount() const;
		/// Returns the number of affected rows.
		/// Used to find out the number of rows affected by insert or update.

	const MetaColumn& metaColumn(std::size_t pos) const;
		/// Returns column meta data.

	bool hasNext();
		/// Returns true if a call to next() will return data.

	std::size_t next();
		/// Retrieves the next row or set of rows from the resultset.
		/// Will throw, if the resultset is empty.

	bool canBind() const;
		/// Returns true if a valid statement is set and we can bind.

	bool canCompile() const;
		/// Returns true if statement was not compiled.

	void compileImpl();
		/// Compiles the statement, doesn't bind yet

	void bindImpl();
		/// Binds parameters

	AbstractExtraction::ExtractorPtr extractor();
		/// Returns the concrete extractor used by the statement.

	AbstractBinding::BinderPtr binder();
		/// Returns the concrete binder used by the statement.

private:
	AbstractBinding::BinderPtr        _ptrBinder;
	AbstractExtraction::ExtractorPtr  _ptrExtractor;
	Poco::SharedPtr<Preparator>       _ptrPreparation;
	bool                              _compiled; 
};


//
// inlines
//
inline AbstractExtraction::ExtractorPtr TestStatementImpl::extractor()
{
	return _ptrExtractor;
}


inline AbstractBinding::BinderPtr TestStatementImpl::binder()
{
	return _ptrBinder;
}


inline std::size_t TestStatementImpl::affectedRowCount() const
{
	return 0;
}


inline bool TestStatementImpl::canCompile() const
{
	return !_compiled;
}


} } } // namespace Poco::Data::Test


#endif // Data_Test_TestStatementImpl_INCLUDED
