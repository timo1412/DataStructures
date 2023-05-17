#pragma once

// Release date 18.08.2021

namespace LHerdaUtils
{
	using namespace System;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;
	using namespace System::Collections::Specialized;

	DialogResult ShowMessageBox(String ^text, MessageBoxIcon icon = MessageBoxIcon::Error, MessageBoxButtons buttons = MessageBoxButtons::OK);

	public ref class AbortException : Exception
	{
	public:
		AbortException() : Exception() {}
	};

	public ref class TerminateException : Exception
	{
	public:
		TerminateException(Exception ^innerException) : Exception(String::Empty, innerException) {}
	};

	Exception^ NewExc(String ^message);
	System::Void ThrowExc(String ^message);
	System::Void ThrowTerminateExc(Exception ^innerException);
	DialogResult ShowExceptionDialog(Exception ^exc);

	String^ Left(String ^value, Int32 count);
	String^ Right(String ^value, Int32 count);

	String^ ReplaceNewLine(String ^value, String ^replaceWith);
	String^ ReplaceNewLineWithSpace(String ^value);

	Object^ DBNullOf(Object ^value);

	Object^ ObjectOf(Byte value, Boolean isNull);
	Boolean SetByte(Object ^value, Byte %outValue, Byte nullValue = 0);
	Byte ByteOf(Object ^value, Byte nullValue = 0);

	Object^ ObjectOf(Int16 value, Boolean isNull);
	Boolean SetInt16(Object ^value, Int16 %outValue, Int16 nullValue = 0);
	Int16 Int16Of(Object ^value, Int16 nullValue = 0);

	Object^ ObjectOf(Int32 value, Boolean isNull);
	//Object^ ObjectOf(Int32 value, Int32 nullValue = 0);
	Boolean SetInt32(Object ^value, Int32 %outValue, Int32 nullValue = 0);
	Int32 Int32Of(Object ^value, Int32 nullValue = 0);

	Object^ ObjectOf(Boolean value, Boolean isNull);

	Object^ ObjectOf(DateTime ^value, Boolean isNull);
	Boolean SetDateTime(Object ^value, DateTime ^%outValue, DateTime ^nullValue = nullptr);
	DateTime^ DateTimeOf(Object ^value, DateTime ^nullValue = nullptr);

	Object^ ObjectOf(String ^value, Boolean isNull);
	//Object^ ObjectOf(String ^value, String ^nullValue = String::Empty);
	Boolean SetString(Object ^value, String ^%outValue, String ^nullValue = String::Empty);
	String^ StringOf(Object ^value, String ^default = String::Empty);

	//String^ StringOf(const char *value);
	//String^ StringOf(const wchar_t *value);
	//String^ StringOf(CString &value);
	//String^ StringOf(CStringW &value);

	public interface class IKeyValue
	{
		property Object^ Key
		{
			virtual Object^ get();
		}

		property Object^ Value
		{
			virtual Object^ get();
		}
	};

	Object^ FindValue(System::Collections::Generic::ICollection<IKeyValue^> ^list, Object ^key);
	
	generic<typename TKey, typename TValue> ref class KeyValue : IKeyValue
	{
	public:
		TKey key;
		TValue value;
		KeyValue(TKey key, TValue value) : key(key), value(value) {}
		property Object^ Key { virtual Object^ get() { return key; } }
		property Object^ Value { virtual Object^ get() { return value; } }
	};

	typedef KeyValue<Byte, String^> KeyValueByteString;
	typedef KeyValue<Int32, String^> KeyValueInt32String;
	typedef KeyValue<Object^, String^> KeyValueObjectString;

	public ref class KeyValueEmpty : IKeyValue
	{
	public:
		property Object^ Key { virtual Object^ get(); }
		property Object^ Value { virtual Object^ get(); }
	};

	generic<typename TKey, typename TValue> Boolean GetKeyValue(TKey key, TValue %value, System::Collections::Generic::IDictionary<TKey, TValue> ^dictionary);
	generic<typename TKey, typename TValue> TValue GetKeyValue(TKey key, System::Collections::Generic::IDictionary<TKey, TValue> ^dictionary);

	generic<typename T> String^ GetCommaList(array<T> ^values);
	generic<typename T> String^ GetCommaList(System::Collections::Generic::IEnumerable<T> ^values);
	array<String^>^ GetListFromStringList(String ^stringList, ... array<String^> ^separators);

	ref class WildcardComparer
	{
	private:
		enum class WildcardPatternType { Nothing, All, Equals, Expression };
		String ^pattern;
		WildcardPatternType wildcardPatternType;
		System::Text::RegularExpressions::Regex ^regex;
	public:
		WildcardComparer(String ^pattern);
		Boolean Match(String ^wildcardExpression);
		property String^ Pattern { String^ get() { return pattern; } }
	};

	ref class WildcardComparers
	{
	private:
		List<WildcardComparer^> ^listWildcardComparer = gcnew List<WildcardComparer^>;
	public:
		Void Add(String ^pattern);
		Void Add(array<String^> ^patternList);
		Boolean Match(String ^wildcardExpression);
	};

	//Boolean MatchWildcardExpression(String ^wildcardExpression, String ^pattern);

	Object^ GetInstanceFieldValue(Object ^instance, String ^fieldName);

	Int16 GetMinuteOf(DateTime value);
	System::Void DecDay(DateTime %dateTime);
	System::Void IncDay(DateTime %dateTime);



	ref class PathInMemory
	{
	private:
		ref class FileInMemory
		{
		public:
			String ^fileName;
			MemoryStream ^memoryStream;
			FileInMemory(String ^fileName, MemoryStream ^memoryStream) : fileName(fileName), memoryStream(memoryStream) {}
		};
	public:
		String ^path;
		List<String^> ^savedFilePathList = gcnew(List<String^>);
		List<FileInMemory^> ^fileInMemoryList = gcnew List<FileInMemory^>;
		PathInMemory(String ^path) : path(path) {}
		System::Void AddFile(String ^fileName, MemoryStream ^memoryStream);
		System::Void DeleteSavedFiles();
		System::Void Save();
	};

	Drawing::Icon^ ResizeIcon(Drawing::Icon ^icon, Drawing::Size ^newSize);

	System::Void SuspendDrawing(Control ^control);
	System::Void ResumeDrawing(Control ^control, Boolean redraw = true);

	System::Void ClearCell(DataGridViewCell ^dataGridViewCell);
	//System::Void ClearSortGlyph(DataGridView ^dataGridView);
	DataGridViewCell^ GetDataGridViewCell(DataGridViewRow ^dataGridViewRow, DataGridViewColumn ^dataGridViewColumn);
	Object^ GetDataGridViewCellValue(DataGridViewRow ^dataGridViewRow, DataGridViewColumn ^dataGridViewColumn);
	System::Boolean IsLastRow(DataGridView ^dataGridView, Int32 indexRow);
	System::Boolean IsLastRow(DataGridViewRow ^dataGridViewRow);
	System::Boolean IsSortedColumn(DataGridView ^dataGridView, Int32 indexColumn);
	System::Boolean IsValid(DataGridView ^dataGridView);
	System::Void SetErrorText(DataGridViewCell ^dataGridViewCell, String ^value, String ^errorText);

	//System::Void DataGridViewCellFormatting(DataGridView ^dataGridView, System::Windows::Forms::DataGridViewCellFormattingEventArgs ^e);
	//System::Void DataGridViewCellValidatingCancelNullValue(DataGridView ^dataGridView, System::Windows::Forms::DataGridViewCellValidatingEventArgs ^e);

	ref class DataGridViewCellValidator;
	ref class DataGridViewColumnValidators;

	typedef List<DataGridViewCellValidator^> ListDataGridViewCellValidator;

	public ref class DataGridViewValidator
	{
	private:
		System::Boolean skipLastRow;
		System::Boolean wasNull;
		List<DataGridViewColumnValidators^> listDataGridViewColumnValidators;
		System::Void DataGridView_CellErrorTextChanged(System::Object ^sender, System::Windows::Forms::DataGridViewCellEventArgs ^e);
		System::Void DataGridView_CellParsing(System::Object ^sender, System::Windows::Forms::DataGridViewCellParsingEventArgs ^e);
		System::Void DataGridView_CellValueChanged(System::Object ^sender, System::Windows::Forms::DataGridViewCellEventArgs ^e);
		System::Void DataGridView_DataError(System::Object ^sender, System::Windows::Forms::DataGridViewDataErrorEventArgs ^e);
		System::Void DataGridView_RowsAdded(System::Object ^sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs ^e);
		System::Void DataGridView_UserDeletedRow(System::Object ^sender, System::Windows::Forms::DataGridViewRowEventArgs ^e);
		DataGridViewColumnValidators^ FindColumnValidators(Int32 indexDataGridViewColumn);
		System::Object^ GetValidatedCellValue(DataGridViewCell ^dataGridViewCell, Object ^valueNew);
		System::Void SetErrorTextNotInList(DataGridViewCell ^dataGridViewCell, String ^value, String ^errorValue);
	public:
		DataGridViewValidator(DataGridView ^dataGridView, Boolean skipLastRow);
		DataGridViewValidator(DataGridView ^dataGridView) : DataGridViewValidator(dataGridView, dataGridView->AllowUserToAddRows) {}
		System::Void Add(DataGridViewColumn ^dataGridViewColumn, ... array<DataGridViewCellValidator^> ^arrayDataGridViewCellValidator);
		System::Void SetCellsValue(DataGridViewRow ^dataGridViewRow, Int32 indexStartColumn, Object ^value);
		System::Void SetCellsValue(DataGridView ^dataGridView, Int32 indexRow, Int32 indexStartColumn, Object ^value);
		System::Void SetText(DataGridViewCell ^dataGridViewCell, String ^value);
		System::Void SetText(DataGridViewRow ^dataGridViewRow, DataGridViewColumn ^dataGridViewColumn, String ^value);
		System::Void SetValue(DataGridViewCell ^dataGridViewCell, Object ^value);
		System::Void SetValue(DataGridViewRow ^dataGridViewRow, DataGridViewColumn ^dataGridViewColumn, Object ^value);
		property System::Boolean SkipLastRow
		{
			System::Boolean get()
			{
				return skipLastRow;
			}
		}
	};

	public ref class DataGridViewColumnValidators
	{
	private:
		DataGridViewColumn ^column;
		ListDataGridViewCellValidator ^validators = gcnew ListDataGridViewCellValidator();
	public:
		DataGridViewColumnValidators(DataGridViewColumn ^dataGridViewColumn) : column(dataGridViewColumn) {}
		System::Void Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew);
		property DataGridViewColumn^ Column { DataGridViewColumn^ get() { return column; } }
		property ListDataGridViewCellValidator^ Validators { ListDataGridViewCellValidator^ get() { return validators; } }
	};

	public ref class DataGridViewCellValidator abstract
	{
	public:
		DataGridViewCellValidator() {}
		System::Boolean Equals(Object ^obj) override;
		virtual System::Void Assign(DataGridViewValidator ^dataGridViewValidator, DataGridViewColumnValidators ^dataGridViewColumnValidators);
		virtual System::String^ Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew) abstract;
		virtual System::Boolean IsConflicted(DataGridViewCellValidator ^dataGridViewCellValidatorCompared, DataGridViewColumnValidators ^dataGridViewColumnValidators);
	};

	public ref class DataGridViewCellValidatorDesiredType : DataGridViewCellValidator
	{
	public:
		DataGridViewCellValidatorDesiredType() : DataGridViewCellValidator() {}
		System::String^ Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew) override;
	};

	// todo: Nefunguje spr·vne
	//public ref class DataGridViewCellValidatorMustEqual : DataGridViewCellValidator
	//{
	//private:
	//	Object ^value;
	//	Int32 indexDataGridViewRow;
	//public:
	//	DataGridViewCellValidatorMustEqual(Object ^value, Int32 indexDataGridViewRow) : DataGridViewCellValidator(), value((value == nullptr || value == String::Empty) ? DBNull::Value : value), indexDataGridViewRow(indexDataGridViewRow) {}
	//	System::String^ Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew) override;
	//};

	public ref class DataGridViewCellValidatorNotNull : DataGridViewCellValidator
	{
	public:
		DataGridViewCellValidatorNotNull() : DataGridViewCellValidator() {}
		System::String^ Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew) override;
	};

	public ref class DataGridViewCellValidatorSetDefNull : DataGridViewCellValidator
	{
	private:
		Object ^defValue;
	public:
		DataGridViewCellValidatorSetDefNull(Object ^defValue) : DataGridViewCellValidator(), defValue(defValue) {}
		System::Boolean Equals(Object ^obj) override;
		System::String^ Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew) override;
		System::Boolean IsConflicted(DataGridViewCellValidator ^dataGridViewCellValidatorCompared, DataGridViewColumnValidators ^dataGridViewColumnValidators) override;
	};

	public ref class DataGridViewCellValidatorTrim : DataGridViewCellValidator
	{
	private:
		array<String^> ^arrKeyword;
	public:
		DataGridViewCellValidatorTrim(... array<String^> ^keywords) : DataGridViewCellValidator(), arrKeyword(keywords) {}
		System::String^ Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew) override;
	};

	//public ref class DataGridViewCellValidatorUnique : DataGridViewCellValidator
	//{
	//	// todo: implementovaù
	//public:
	//	DataGridViewCellValidatorUnique() : DataGridViewCellValidator() {}
	//	System::String^ Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew) override;
	//};

	public ref class DataGridViewCellValidatorRelate abstract : DataGridViewCellValidator
	{
	private:
		DataGridViewColumn ^dataGridViewColumnRelate;
		Int32 previousRowDiff;
		List<DataGridViewColumnValidators^> listRelateDataGridViewColumnValidators;
		Boolean isEventsAssigned;
		Boolean skipLastRow;
		System::Void DataGridView_CellValueChanged(System::Object ^sender, System::Windows::Forms::DataGridViewCellEventArgs ^e);
		System::Void DataGridView_RowsRemoved(System::Object ^sender, System::Windows::Forms::DataGridViewRowsRemovedEventArgs ^e);
		System::Void ExecuteRelateDataGridViewColumnValidators(DataGridView ^dataGridView, Int32 indexRow);
	protected:
		virtual System::String^ Calc(Object ^valueRelate, Object ^%valueNew) abstract;
		System::String^ GetMessage(String ^message);
	public:
		DataGridViewCellValidatorRelate(DataGridViewColumn ^dataGridViewColumnRelate, Int32 previousRowDiff) : DataGridViewCellValidator(), dataGridViewColumnRelate(dataGridViewColumnRelate), previousRowDiff(previousRowDiff) {}
		System::Void Assign(DataGridViewValidator ^dataGridViewValidator, DataGridViewColumnValidators ^dataGridViewColumnValidators) override;
		System::Boolean Equals(Object ^obj) override;
		System::String^ Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew) override;
	};

	//public ref class DataGridViewCellValidatorEqual : DataGridViewCellValidatorRelate
	//{
	//private:
	//	Boolean negation;
	//protected:
	//	System::String^ Calc(Object ^valueRelate, Object ^%valueNew) override;
	//public:
	//	DataGridViewCellValidatorEqual(DataGridViewColumn ^dataGridViewColumnRelate, Int32 previousRowDiff, Boolean negation) : DataGridViewCellValidatorRelate(dataGridViewColumnRelate, previousRowDiff), negation(negation) {}
	//};

	public ref class DataGridViewCellValidatorRelateInt32 abstract : DataGridViewCellValidatorRelate
	{
	protected:
		System::String^ Calc(Object ^valueRelate, Object ^%valueNew) override;
		virtual System::String^ Calc(Int32 valueRelate, Int32 valueNew) abstract;
	public:
		DataGridViewCellValidatorRelateInt32(DataGridViewColumn ^dataGridViewColumnRelate, Int32 previousRowDiff) : DataGridViewCellValidatorRelate(dataGridViewColumnRelate, previousRowDiff) {}
	};

	public ref class DataGridViewCellValidatorMustBeDiff : DataGridViewCellValidatorRelateInt32
	{
	protected:
		Int32 diffValue;
		System::String^ Calc(Int32 valueRelate, Int32 valueNew) override;
	public:
		DataGridViewCellValidatorMustBeDiff(DataGridViewColumn ^dataGridViewColumnRelate, Int32 previousRowDiff, Int32 diffValue) : DataGridViewCellValidatorRelateInt32(dataGridViewColumnRelate, previousRowDiff), diffValue(diffValue) {}
		System::Boolean Equals(Object ^obj) override;
		System::Boolean IsConflicted(DataGridViewCellValidator ^dataGridViewCellValidatorCompared, DataGridViewColumnValidators ^dataGridViewColumnValidators) override;
	};

	//public ref class DataGridViewCellValidatorMustBeGreater : DataGridViewCellValidatorRelateInt32
	//{
	//protected:
	//	System::String^ Calc(Int32 valueRelate, Int32 valueNew) override;
	//public:
	//	DataGridViewCellValidatorMustBeGreater(DataGridViewColumn ^dataGridViewColumnRelate, Int32 previousRowDiff) : DataGridViewCellValidatorRelateInt32(dataGridViewColumnRelate, previousRowDiff) {}
	//};

	public ref class DataGridViewCellValidatorNotLess : DataGridViewCellValidatorRelateInt32
	{
	protected:
		System::String^ Calc(Int32 valueRelate, Int32 valueNew) override;
	public:
		DataGridViewCellValidatorNotLess(DataGridViewColumn ^dataGridViewColumnRelate, Int32 previousRowDiff) : DataGridViewCellValidatorRelateInt32(dataGridViewColumnRelate, previousRowDiff) {}
	};

	public ref class DataGridViewCellValidatorSetDiff : DataGridViewCellValidatorMustBeDiff
	{
	protected:
		System::String^ Calc(Object ^valueRelate, Object ^%valueNew) override;
	public:
		DataGridViewCellValidatorSetDiff(DataGridViewColumn ^dataGridViewColumnRelate, Int32 previousRowDiff, Int32 diffValue) : DataGridViewCellValidatorMustBeDiff(dataGridViewColumnRelate, previousRowDiff, diffValue) {}
	};

	public ref class NumericUpDownEditingControl : NumericUpDown, IDataGridViewEditingControl
	{
	private:
		DataGridView ^dataGridViewControl;
		Int32 indexRow;
		Decimal valueOld;
	protected:
		Void OnValidated(EventArgs ^eventArgs) override;
	public:
		//NumericUpDownEditingControl::NumericUpDownEditingControl();
		virtual Void ApplyCellStyleToEditingControl(DataGridViewCellStyle ^dataGridViewCellStyle);
		virtual Boolean EditingControlWantsInputKey(Keys key, Boolean dataGridViewWantsInputKey);
		virtual Object^ GetEditingControlFormattedValue(DataGridViewDataErrorContexts context);
		virtual Void PrepareEditingControlForEdit(Boolean selectAll);
		property System::Windows::Forms::Cursor^ EditingControlCursor { System::Windows::Forms::Cursor^ get(); }
		property DataGridView^ EditingControlDataGridView { virtual DataGridView^ get(); virtual Void set(DataGridView ^value); }
		property Object^ EditingControlFormattedValue { virtual Object^ get(); virtual Void set(Object ^value); }
		property Int32 EditingControlRowIndex { virtual Int32 get(); virtual Void set(Int32 value); }
		property Boolean EditingControlValueChanged { virtual Boolean get(); virtual Void set(Boolean value); }
		property System::Windows::Forms::Cursor^ EditingPanelCursor { virtual System::Windows::Forms::Cursor^ get(); }
		property Boolean RepositionEditingControlOnValueChange { virtual Boolean get(); }
	};

	public ref class NumericUpDownCell : DataGridViewTextBoxCell
	{
	public:
		NumericUpDownCell();
		//property Object^ DefaultNewRowValue { Object^ get() override; }
		property Type^ EditType { Type^ get() override; }
		property Type^ ValueType { Type^ get() override; }
		Void InitializeEditingControl(Int32 rowIndex, Object ^initialFormattedValue, DataGridViewCellStyle ^dataGridViewCellStyle) override;
	};

	public ref class DataGridViewNumericUpDownColumn : DataGridViewColumn
	{
	public:
		DataGridViewNumericUpDownColumn(DataGridViewCell ^cell) : DataGridViewColumn(cell) {}
		DataGridViewNumericUpDownColumn() : DataGridViewColumn(gcnew NumericUpDownCell()) {}
		property DataGridViewCell^ CellTemplate { DataGridViewCell^ get() override; Void set(DataGridViewCell ^value) override; }
	};

	String^ SqlValueOf(String ^value);
	String^ SqlValueOf(Double ^value);
	String^ SqlValueOf(DateTime value);
	String^ SqlValueOf(Object ^value);
	String^ SqlValueOf(DataGridViewCell ^value);

	public ref class Statics
	{
	private:
		static DataGridViewCellEventHandler ^dataGridViewCellClickHeaderEndEditEventHandler;
		static DataGridViewDataErrorEventHandler ^dataGridViewDataErrorThrowExceptionEventHandler;
		static DataGridViewRowCancelEventHandler ^dataGridViewUserDeletingRowConfirmEventHandler;
		static DataGridViewRowCancelEventHandler ^dataGridViewUserDeletingRowConfirmExceptLastEventHandler;
		static DataGridViewCellValidatorNotNull ^dataGridViewCellValidatorNotNullCommon;
		static DataGridViewCellValidatorTrim ^dataGridViewCellValidatorTrimCommon;
		static System::Drawing::Color colorTextReadOnly = System::Drawing::Color::DimGray;
		static KeyValueEmpty ^itemKeyValueEmpty;
		static DateTime nullDateTime;
	public:
		static Boolean IsNull(DateTime value);
		//	System::Void dataGridView_UserDeletingRow(System::Object ^sender, System::Windows::Forms::DataGridViewRowCancelEventArgs ^e);
		//	System::Void dataGridViewInt_SortCompare(System::Object ^sender, System::Windows::Forms::DataGridViewSortCompareEventArgs ^e);
		static System::Void DataGridViewCellClickHeaderEndEdit(System::Object ^sender, System::Windows::Forms::DataGridViewCellEventArgs ^e);
		static System::Void DataGridViewDataErrorThrowException(System::Object ^sender, System::Windows::Forms::DataGridViewDataErrorEventArgs ^e);
		static System::Void DataGridViewUserDeletingRowConfirm(System::Object ^sender, System::Windows::Forms::DataGridViewRowCancelEventArgs ^e);
		static System::Void DataGridViewUserDeletingRowConfirmExceptLast(System::Object ^sender, System::Windows::Forms::DataGridViewRowCancelEventArgs ^e);
		static property DataGridViewCellEventHandler^ DataGridViewCellClickHeaderEndEditEventHandler { DataGridViewCellEventHandler^ get(); }
		static property DataGridViewDataErrorEventHandler^ DataGridViewDataErrorThrowExceptionEventHandler { DataGridViewDataErrorEventHandler^ get(); }
		static property DataGridViewRowCancelEventHandler^ DataGridViewUserDeletingRowConfirmEventHandler { DataGridViewRowCancelEventHandler^ get(); }
		static property DataGridViewRowCancelEventHandler^ DataGridViewUserDeletingRowConfirmExceptLastEventHandler { DataGridViewRowCancelEventHandler^ get(); }
		static property DataGridViewCellValidatorNotNull^ DataGridViewCellValidatorNotNullCommon { DataGridViewCellValidatorNotNull^ get(); }
		static property DataGridViewCellValidatorTrim^ DataGridViewCellValidatorTrimCommon { DataGridViewCellValidatorTrim^ get(); }
		static property System::Drawing::Color ColorTextReadOnly { System::Drawing::Color get(); }
		static property KeyValueEmpty^ ItemKeyValueEmpty { KeyValueEmpty^ get(); }
		static property DateTime NullDateTime { DateTime get(); }
	};
}