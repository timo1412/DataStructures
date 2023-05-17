#ifdef _MSC_VER
#pragma comment(lib, "user32.lib")
#endif

#include <windows.h>
#include "LHerdaUtils.h"

namespace LHerdaUtils
{
	DialogResult ShowMessageBox(String ^text, MessageBoxIcon icon, MessageBoxButtons buttons)
	{
		MessageBoxDefaultButton defaultButton = MessageBoxDefaultButton::Button1;
		String ^caption;
		switch (icon)
		{
			case MessageBoxIcon::Error:
				caption = "Pozor";
				break;
			case MessageBoxIcon::Question:
				caption = "Potvrdenie";
				if (buttons == MessageBoxButtons::OK)
					buttons = MessageBoxButtons::YesNo;
				defaultButton = MessageBoxDefaultButton::Button2;
				break;
			case MessageBoxIcon::Warning:
				caption = "Upozornenie";
				if (buttons != MessageBoxButtons::OK)
					defaultButton = MessageBoxDefaultButton::Button2;
				break;
			default:
				caption = "Inform·cia";
				break;
		}
		return MessageBox::Show(text, caption, buttons, icon, defaultButton);
	}

	Exception^ NewExc(String ^message)
	{
		return gcnew Exception(message);
	}

	Void ThrowExc(String ^message)
	{
		throw NewExc(message);
	}

	System::Void ThrowTerminateExc(Exception ^innerException)
	{
		throw gcnew TerminateException(innerException);
	}

	Void ThrowExcProcName()
	{
		ThrowExc(Diagnostics::StackTrace().GetFrame(1)->GetMethod()->Name);
	}

	DialogResult ShowExceptionDialog(Exception ^exc)
	{
		return ThreadExceptionDialog(exc).ShowDialog();
	}

	String^ Left(String ^value, Int32 count)
	{
		return value->Remove(count);
	}

	String^ Right(String ^value, Int32 count)
	{
		return value->Substring(value->Length - count, count);
	}

	String^ ReplaceNewLine(String ^value, String ^replaceWith)
	{
		return value->Replace("\r\n", replaceWith)->Replace("\r", replaceWith)->Replace("\n", replaceWith);
	}

	String^ ReplaceNewLineWithSpace(String ^value)
	{
		return ReplaceNewLine(value, " ");
	}

	Object^ DBNullOf(Object ^value)
	{
		if (value)
			return value;
		return DBNull::Value;
	}

	Object^ ObjectOf(Byte value, Boolean isNull)
	{
		if (isNull)
			return DBNull::Value;
		return value;
	}

	Boolean SetByte(Object ^value, Byte %outValue, Byte nullValue)
	{
		if (Convert::IsDBNull(value))
		{
			outValue = nullValue;
			return false;
		}
		outValue = safe_cast<Byte>(value);
		return true;
	}

	Byte ByteOf(Object ^value, Byte nullValue)
	{
		Byte outValue;
		SetByte(value, outValue, nullValue);
		return outValue;
	}

	Object^ ObjectOf(Int16 value, Boolean isNull)
	{
		if (isNull)
			return DBNull::Value;
		return value;
	}

	Boolean SetInt16(Object ^value, Int16 %outValue, Int16 nullValue)
	{
		if (Convert::IsDBNull(value))
		{
			outValue = nullValue;
			return false;
		}
		outValue = safe_cast<Int16>(value);
		return true;
	}

	Int16 Int16Of(Object ^value, Int16 nullValue)
	{
		Int16 outValue;
		SetInt16(value, outValue, nullValue);
		return outValue;
	}

	Object^ ObjectOf(Int32 value, Boolean isNull)
	{
		if (isNull)
			return DBNull::Value;
		return value;
	}

	//Object^ ObjectOf(Int32 value, Int32 nullValue)
	//{
	//	return ObjectOf(value, value == nullValue);
	//}

	Boolean SetInt32(Object ^value, Int32 %outValue, Int32 nullValue)
	{
		if (Convert::IsDBNull(value))
		{
			outValue = nullValue;
			return false;
		}
		outValue = safe_cast<Int32>(value);
		return true;
	}

	Int32 Int32Of(Object ^value, Int32 nullValue)
	{
		Int32 outValue;
		SetInt32(value, outValue, nullValue);
		return outValue;
	}

	Object^ ObjectOf(Boolean value, Boolean isNull)
	{
		if (isNull)
			return DBNull::Value;
		return value;
	}

	Object^ ObjectOf(DateTime ^value, Boolean isNull)
	{
		if (isNull)
			return DBNull::Value;
		return value;
	}

	Boolean SetDateTime(Object ^value, DateTime ^%outValue, DateTime ^nullValue)
	{
		if (Convert::IsDBNull(value))
		{
			outValue = nullValue;
			return false;
		}
		outValue = safe_cast<DateTime^>(value);
		return true;
	}

	DateTime^ DateTimeOf(Object ^value, DateTime ^nullValue)
	{
		DateTime ^outValue;
		SetDateTime(value, outValue, nullValue);
		return outValue;
	}

	Object^ ObjectOf(String ^value, Boolean isNull)
	{
		if (isNull)
			return DBNull::Value;
		return value;
	}

	//Object^ ObjectOf(String ^value, String ^nullValue)
	//{
	//	return ObjectOf(value, value == nullValue);
	//}

	Boolean SetString(Object ^value, String ^%outValue, String ^nullValue)
	{
		if (Convert::IsDBNull(value))
		{
			outValue = nullValue;
			return false;
		}
		outValue = safe_cast<String^>(value);
		return true;
	}

	String^ StringOf(Object ^value, String ^nullValue)
	{
		String ^outValue;
		SetString(value, outValue, nullValue);
		return outValue;
	}

	//String^ StringOf(const char *value)
	//{
	//	return gcnew String(value);
	//}

	//String^ StringOf(const wchar_t *value)
	//{
	//	return gcnew String(value);
	//}

	//String^ StringOf(CString &value)
	//{
	//	return StringOf((LPCSTR)value);
	//}

	//String^ StringOf(CStringW &value)
	//{
	//	return StringOf((LPCWSTR)value);
	//}

	Object^ FindValue(System::Collections::Generic::ICollection<IKeyValue^> ^list, Object ^key)
	{
		for each (IKeyValue ^keyValue in list)
			if (keyValue->Key->Equals(key))
				return keyValue->Value;
		return nullptr;
	}

	Object^ KeyValueEmpty::Key::get()
	{
		return DBNull::Value;
	}

	Object^ KeyValueEmpty::Value::get()
	{
		return Key;
	}

	generic<typename TKey, typename TValue> Boolean GetKeyValue(TKey key, TValue %value, System::Collections::Generic::IDictionary<TKey, TValue> ^dictionary)
	{
		if (dictionary->TryGetValue(key, value))
			return true;
		value = Activator::CreateInstance<TValue>();
		dictionary->Add(key, value);
		return false;
	}

	generic<typename TKey, typename TValue> TValue GetKeyValue(TKey key, System::Collections::Generic::IDictionary<TKey, TValue> ^dictionary)
	{
		TValue value;
		GetKeyValue(key, value, dictionary);
		return value;
	}

	generic<typename T> String^ GetCommaList(array<T> ^values)
	{
		return String::Join(",", values);
	}

	generic<typename T> String^ GetCommaList(System::Collections::Generic::IEnumerable<T> ^values)
	{
		return String::Join(",", values);
	}

	array<String^>^ GetListFromStringList(String ^stringList, ... array<String^> ^separators)
	{
		return stringList->Split(separators, StringSplitOptions::RemoveEmptyEntries);
	}

	WildcardComparer::WildcardComparer(String ^pattern)
	{
		this->pattern = pattern->Trim();
		if (this->pattern->Equals(String::Empty))
			this->wildcardPatternType = WildcardPatternType::Nothing;
		else if (this->pattern->Equals("*"))
			this->wildcardPatternType = WildcardPatternType::All;
		else if (this->pattern->IndexOfAny(gcnew array<wchar_t>{ '*', '?' }) < 0)
			this->wildcardPatternType = WildcardPatternType::Equals;
		else
		{
			this->wildcardPatternType = WildcardPatternType::Expression;
			this->regex = gcnew System::Text::RegularExpressions::Regex("^" + System::Text::RegularExpressions::Regex::Escape(this->pattern)->Replace(R"(\*)", ".*")->Replace(R"(\?)", ".") + "$", System::Text::RegularExpressions::RegexOptions::Compiled | System::Text::RegularExpressions::RegexOptions::IgnoreCase | System::Text::RegularExpressions::RegexOptions::Singleline);
		}
	}

	Boolean WildcardComparer::Match(String ^wildcardExpression)
	{
		if (this->wildcardPatternType < WildcardPatternType::Equals)
			return this->wildcardPatternType == WildcardPatternType::All;
		wildcardExpression = wildcardExpression->Trim();
		if (wildcardExpression->Equals(String::Empty))
			return false;
		if (regex)
			return this->regex->IsMatch(wildcardExpression);
		else
			return this->pattern->Equals(wildcardExpression, StringComparison::OrdinalIgnoreCase);
	}

	Void WildcardComparers::Add(String ^pattern)
	{
		pattern = pattern->Trim();
		Int32 indexListWildcardComparer = listWildcardComparer->Count;
		while (--indexListWildcardComparer >= 0 && !listWildcardComparer[indexListWildcardComparer]->Pattern->Equals(pattern));
		if (indexListWildcardComparer < 0)
			listWildcardComparer->Add(gcnew WildcardComparer(pattern));
	}

	Void WildcardComparers::Add(array<String^> ^patternList)
	{
		for each(String ^expression in patternList)
			Add(expression);
	}

	Boolean WildcardComparers::Match(String ^wildcardExpression)
	{
		Int32 indexListPattern = listWildcardComparer->Count;
		if (!indexListPattern)
			return wildcardExpression->Equals(String::Empty);
		do
		{
			if (listWildcardComparer[--indexListPattern]->Match(wildcardExpression))
				return true;
		} while (indexListPattern);
		return false;
	}

	//Boolean MatchWildcardExpression(String ^wildcardExpression, String ^pattern)
	//{
	//	return gcnew WildcardComparer(pattern)->Match(wildcardExpression);
	//}

	Object^ GetInstanceFieldValue(Object ^instance, String ^fieldName)
	{
		return instance->GetType()->GetField(fieldName, Reflection::BindingFlags::Instance | Reflection::BindingFlags::Public | Reflection::BindingFlags::NonPublic | Reflection::BindingFlags::Static)->GetValue(instance);
	}

	Int16 GetMinuteOf(DateTime value)
	{
		return value.Hour * 60 + value.Minute/* + (value.Second > 0)*/;
	}

	System::Void DecDay(DateTime %dateTime)
	{
		dateTime = dateTime.AddDays(-1);
	}

	System::Void IncDay(DateTime %dateTime)
	{
		dateTime = dateTime.AddDays(1);
	}



	System::Void PathInMemory::AddFile(String ^fileName, MemoryStream ^memoryStream)
	{
		fileInMemoryList->Add(gcnew FileInMemory(fileName, memoryStream));
	}

	System::Void PathInMemory::DeleteSavedFiles()
	{
		for each (String ^filePath in savedFilePathList)
			File::Delete(filePath);
	}

	System::Void PathInMemory::Save()
	{
		for each (FileInMemory ^fileInMemory in fileInMemoryList)
		{
			String ^filePath = path + fileInMemory->fileName;
			FileStream ^fileStream = gcnew FileStream(filePath, FileMode::Create);
			try
			{
				savedFilePathList->Add(filePath);
				fileInMemory->memoryStream->CopyTo(fileStream);
			}
			finally
			{
				fileStream->Close(); // MusÌ byù pre dokonËenie z·pisu
			}
		}
	}

	Drawing::Icon^ ResizeIcon(Drawing::Icon ^icon, Drawing::Size ^newSize)
	{
		Drawing::Bitmap ^bitmap = gcnew Drawing::Bitmap(newSize->Width, newSize->Height);
		Drawing::Graphics ^graphics = Drawing::Graphics::FromImage(bitmap);
		graphics->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::HighQualityBicubic;
		graphics->DrawImage(icon->ToBitmap(), *gcnew Drawing::Rectangle(Drawing::Point::Empty, *newSize));
		return Drawing::Icon::FromHandle(bitmap->GetHicon());
	}

	System::Void SetRedraw(Control ^control, Boolean value)
	{
		SendMessage(static_cast<HWND>(control->Handle.ToPointer()), WM_SETREDRAW, value, 0);
	}

	System::Void SuspendDrawing(Control ^control)
	{
		SetRedraw(control, false);
	}

	System::Void ResumeDrawing(Control ^control, Boolean redraw)
	{
		SetRedraw(control, true);
		if (redraw)
			control->Refresh();
	}

	System::Void ClearCell(DataGridViewCell ^dataGridViewCell)
	{
		SetErrorText(dataGridViewCell, String::Empty, String::Empty);
	}

	//System::Void ClearSortGlyph(DataGridView ^dataGridView)
	//{
	//	if (dataGridView->SortedColumn)
	//		dataGridView->SortedColumn->HeaderCell->SortGlyphDirection = SortOrder::None;
	//}

	DataGridViewCell^ GetDataGridViewCell(DataGridViewRow ^dataGridViewRow, DataGridViewColumn ^dataGridViewColumn)
	{
		return dataGridViewRow->Cells[dataGridViewColumn->Index];
	}

	Object^ GetDataGridViewCellValue(DataGridViewRow ^dataGridViewRow, DataGridViewColumn ^dataGridViewColumn)
	{
		return GetDataGridViewCell(dataGridViewRow, dataGridViewColumn)->Value;
	}

	System::Boolean IsLastRow(DataGridView ^dataGridView, Int32 indexRow)
	{
		return indexRow == dataGridView->RowCount - 1;
	}

	System::Boolean IsLastRow(DataGridViewRow ^dataGridViewRow)
	{
		return IsLastRow(dataGridViewRow->DataGridView, dataGridViewRow->Index);
	}

	System::Boolean IsSortedColumn(DataGridView ^dataGridView, Int32 indexColumn)
	{
		return dataGridView->SortedColumn && dataGridView->SortedColumn->Index == indexColumn;
	}

	System::Boolean IsValid(DataGridView ^dataGridView)
	{
		for each (DataGridViewRow ^dataGridViewRow in dataGridView->Rows)
		{
			if (!dataGridViewRow->ErrorText->Equals(String::Empty))
				for each (DataGridViewCell ^dataGridViewCell in dataGridViewRow->Cells)
				{
					if (!dataGridViewCell->ErrorText->Equals(String::Empty))
					{
						ShowMessageBox("Tabuæka obsahuje neplatnÈ ˙daje.");
						dataGridView->CurrentCell = dataGridViewCell;
						dataGridView->BeginEdit(true);
						return false;
					}
				}
		}
		return true;
	}

	System::Void SetErrorText(DataGridViewCell ^dataGridViewCell, String ^value, String ^errorText)
	{
		dataGridViewCell->ErrorText = errorText;
		dataGridViewCell->Style->NullValue = value;
		dataGridViewCell->Value = nullptr;
	}

	//System::Void DataGridViewCellSetFormatValue(DataGridView ^dataGridView, System::Windows::Forms::DataGridViewCellFormattingEventArgs ^e, DataGridViewCell ^dataGridViewCell, Object ^value)
	//{
	//	if (dataGridView->CurrentCell == dataGridViewCell)
	//		e->Value = DBNull::Value;
	//	else
	//	{
	//		e->Value = value;
	//		e->FormattingApplied = true;
	//	}
	//}

	//System::Void DataGridViewCellFormatting(DataGridView ^dataGridView, System::Windows::Forms::DataGridViewCellFormattingEventArgs ^e)
	//{
	//	if (e->Value)
	//	{
	//		DataGridViewCell ^dataGridViewCell = dataGridView[e->ColumnIndex, e->RowIndex];
	//		if (dataGridViewCell->ReadOnly)
	//			e->CellStyle->ForeColor = GlobalVariables::ColorTextReadOnly;
	//		if (e->Value->GetType() == Int32::typeid)
	//		{
	//			Int32 intValue = safe_cast<Int32>(e->Value);
	//			if (intValue == Int32::MaxValue)
	//				DataGridViewCellSetFormatValue(dataGridView, e, dataGridViewCell, "<max>");
	//			else
	//				if (intValue == Int32::MinValue)
	//					DataGridViewCellSetFormatValue(dataGridView, e, dataGridViewCell, "<min>");
	//		}
	//	}
	//}

	//System::Void DataGridViewCellValidatingCancelNullValue(DataGridView ^dataGridView, System::Windows::Forms::DataGridViewCellValidatingEventArgs ^e)
	//{
	//	dataGridView[e->ColumnIndex, e->RowIndex]->ErrorText = (dataGridView->IsCurrentRowDirty && e->FormattedValue->Equals(String::Empty)) ? "PolÌËko musÌ byù vyplnenÈ." : String::Empty;
	//}

	DataGridViewValidator::DataGridViewValidator(DataGridView ^dataGridView, Boolean skipLastRow) : skipLastRow(skipLastRow)
	{
		dataGridView->CellErrorTextChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &DataGridViewValidator::DataGridView_CellErrorTextChanged);
		dataGridView->CellParsing += gcnew System::Windows::Forms::DataGridViewCellParsingEventHandler(this, &DataGridViewValidator::DataGridView_CellParsing);
		dataGridView->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &DataGridViewValidator::DataGridView_CellValueChanged);
		dataGridView->DataError += gcnew System::Windows::Forms::DataGridViewDataErrorEventHandler(this, &DataGridViewValidator::DataGridView_DataError);
		dataGridView->RowsAdded += gcnew System::Windows::Forms::DataGridViewRowsAddedEventHandler(this, &DataGridViewValidator::DataGridView_RowsAdded);
		dataGridView->UserDeletedRow += gcnew System::Windows::Forms::DataGridViewRowEventHandler(this, &DataGridViewValidator::DataGridView_UserDeletedRow);
		DataGridViewCellValidatorDesiredType ^dataGridViewCellValidatorDesiredType = gcnew DataGridViewCellValidatorDesiredType();
		for each (DataGridViewColumn ^dataGridViewColumn in dataGridView->Columns)
			Add(dataGridViewColumn, dataGridViewCellValidatorDesiredType);
	}

	System::Void DataGridViewValidator::Add(DataGridViewColumn ^dataGridViewColumn, ... array<DataGridViewCellValidator^> ^arrayDataGridViewCellValidator)
	{
		DataGridViewColumnValidators ^dataGridViewColumnValidators = FindColumnValidators(dataGridViewColumn->Index);
		if (!dataGridViewColumnValidators)
		{
			dataGridViewColumnValidators = gcnew DataGridViewColumnValidators(dataGridViewColumn);
			listDataGridViewColumnValidators.Add(dataGridViewColumnValidators);
		}
		Boolean isConflicted = false;
		for each (DataGridViewCellValidator ^dataGridViewCellValidatorNew in arrayDataGridViewCellValidator)
		{
			for each (DataGridViewCellValidator ^dataGridViewCellValidator in dataGridViewColumnValidators->Validators)
				if (isConflicted = dataGridViewCellValidatorNew->IsConflicted(dataGridViewCellValidator, dataGridViewColumnValidators))
					break;
			if (!isConflicted)
				dataGridViewCellValidatorNew->Assign(this, dataGridViewColumnValidators);
		}
	}

	System::Void DataGridViewValidator::DataGridView_CellErrorTextChanged(System::Object ^sender, System::Windows::Forms::DataGridViewCellEventArgs ^e)
	{
		// todo: robiù len raz po valid·cii, keÔ s˙ uû vöetky cell->ErrorText zn·me
		if (e->RowIndex < 0)
			return;
		DataGridViewRow ^dataGridViewRow = safe_cast<DataGridView^>(sender)->Rows[e->RowIndex];
		if (dataGridViewRow->Cells[e->ColumnIndex]->ErrorText->Equals(String::Empty))
		{
			if (!dataGridViewRow->ErrorText->Equals(String::Empty))
			{
				for each (DataGridViewCell ^dataGridViewCell in dataGridViewRow->Cells)
					if (!dataGridViewCell->ErrorText->Equals(String::Empty))
						return;
				dataGridViewRow->ErrorText = String::Empty;
			}
		}
		else
			if (dataGridViewRow->ErrorText->Equals(String::Empty))
				dataGridViewRow->ErrorText = "V riadku s˙ neplatnÈ ˙daje";
	}

	System::Void DataGridViewValidator::DataGridView_CellParsing(System::Object ^sender, System::Windows::Forms::DataGridViewCellParsingEventArgs ^e)
	{
		if (e->ParsingApplied)
			return;
		DataGridView ^dataGridView = safe_cast<DataGridView^>(sender);
		if (skipLastRow && IsLastRow(dataGridView, e->RowIndex))
			return;
		DataGridViewCell ^dataGridViewCell = dataGridView[e->ColumnIndex, e->RowIndex];
		if (!e->Value->Equals(String::Empty) && e->Value->Equals(e->InheritedCellStyle->NullValue))
		{
			wasNull = !dataGridViewCell->Value;
			return;
		}
		e->Value = GetValidatedCellValue(dataGridViewCell, e->Value);
		if (Convert::IsDBNull(e->Value) || !dynamic_cast<DataGridViewComboBoxColumn^>(dataGridViewCell->OwningColumn))
			e->ParsingApplied = true;
	}

	System::Void DataGridViewValidator::DataGridView_CellValueChanged(System::Object ^sender, System::Windows::Forms::DataGridViewCellEventArgs ^e)
	{
		if (wasNull)
		{
			wasNull = false;
			safe_cast<DataGridView^>(sender)[e->ColumnIndex, e->RowIndex]->Value = nullptr;
		}
	}

	System::Void DataGridViewValidator::DataGridView_DataError(System::Object ^sender, System::Windows::Forms::DataGridViewDataErrorEventArgs ^e)
	{
		if (System::ArgumentException ^exc = dynamic_cast<System::ArgumentException^>(e->Exception))
			if (exc->Message == "DataGridViewComboBoxCell value is not valid.")
			{
				DataGridViewCell ^dataGridViewCell = safe_cast<DataGridView^>(sender)[e->ColumnIndex, e->RowIndex];
				Object ^value = dataGridViewCell->Value;
				DataGridViewComboBoxColumn ^dataGridViewComboBoxColumn = safe_cast<DataGridViewComboBoxColumn^>(dataGridViewCell->OwningColumn);
				if (dataGridViewComboBoxColumn->ValueMember->Equals(String::Empty))
					SetErrorTextNotInList(dataGridViewCell, value->ToString(), String::Format("'{0}'", value));
				else
					SetErrorTextNotInList(dataGridViewCell, String::Format("<Id: {0}>", value), String::Format("zodpovedaj˙ca identifik·toru '{0}'", value));
				return;
			}
		e->ThrowException = true;
	}

	System::Void DataGridViewValidator::DataGridView_RowsAdded(System::Object ^sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs ^e)
	{
		DataGridView ^dataGridView = safe_cast<DataGridView^>(sender);
		for (Int32 index = skipLastRow && !e->RowIndex; index < e->RowCount; index++)
			for each (DataGridViewCell ^dataGridViewCell in dataGridView->Rows[e->RowIndex + index - skipLastRow]->Cells)
				SetValue(dataGridViewCell, dataGridViewCell->Value);
	}

	System::Void DataGridViewValidator::DataGridView_UserDeletedRow(System::Object ^sender, System::Windows::Forms::DataGridViewRowEventArgs ^e)
	{
		DataGridView ^dataGridView = safe_cast<DataGridView^>(sender);
		if (skipLastRow && dataGridView->AllowUserToAddRows && dataGridView->RowCount > 0 && dataGridView->NewRowIndex < 0)
			for each (DataGridViewCell ^dataGridViewCell in dataGridView->Rows[dataGridView->RowCount - 1]->Cells)
				ClearCell(dataGridViewCell);
	}

	DataGridViewColumnValidators^ DataGridViewValidator::FindColumnValidators(Int32 indexDataGridViewColumn)
	{
		for each (DataGridViewColumnValidators ^dataGridViewColumnValidators in listDataGridViewColumnValidators)
			if (dataGridViewColumnValidators->Column->Index == indexDataGridViewColumn)
				return dataGridViewColumnValidators;
		return nullptr;
	}

	System::Object^ DataGridViewValidator::GetValidatedCellValue(DataGridViewCell ^dataGridViewCell, Object ^valueNew)
	{
		if (DataGridViewColumnValidators ^dataGridViewColumnValidators = FindColumnValidators(dataGridViewCell->ColumnIndex))
			dataGridViewColumnValidators->Execute(dataGridViewCell, valueNew);
		return valueNew;
	}

	System::Void DataGridViewValidator::SetCellsValue(DataGridViewRow ^dataGridViewRow, Int32 indexStartColumn, Object ^value)
	{
		for (Int32 indexCol = indexStartColumn; indexCol < dataGridViewRow->DataGridView->ColumnCount; indexCol++)
			SetValue(dataGridViewRow->Cells[indexCol], value);
	}

	System::Void DataGridViewValidator::SetCellsValue(DataGridView ^dataGridView, Int32 indexStartColumn, Int32 indexRow, Object ^value)
	{
		SetCellsValue(dataGridView->Rows[indexRow], indexStartColumn, value);
	}

	System::Void DataGridViewValidator::SetErrorTextNotInList(DataGridViewCell ^dataGridViewCell, String ^value, String ^errorValue)
	{
		SetErrorText(dataGridViewCell, value, String::Format("Hodnota {0} sa nenach·dza v zozname", errorValue));
	}

	System::Void DataGridViewValidator::SetText(DataGridViewCell ^dataGridViewCell, String ^value)
	{
		dataGridViewCell->Style->NullValue = value;
		SetValue(dataGridViewCell, nullptr);
	}

	System::Void DataGridViewValidator::SetText(DataGridViewRow ^dataGridViewRow, DataGridViewColumn ^dataGridViewColumn, String ^value)
	{
		SetText(GetDataGridViewCell(dataGridViewRow, dataGridViewColumn), value);
	}

	System::Void DataGridViewValidator::SetValue(DataGridViewCell ^dataGridViewCell, Object ^value)
	{
		dataGridViewCell->Value = /*SkipLastRow && IsLastRow(dataGridViewCell->OwningRow) ? value : */GetValidatedCellValue(dataGridViewCell, value);
	}

	System::Void DataGridViewValidator::SetValue(DataGridViewRow ^dataGridViewRow, DataGridViewColumn ^dataGridViewColumn, Object ^value)
	{
		SetValue(GetDataGridViewCell(dataGridViewRow, dataGridViewColumn), value);
	}

	System::Void DataGridViewColumnValidators::Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew)
	{
		String ^errorText = String::Empty;
		if (valueNew)
		{
			if (Convert::IsDBNull(valueNew))
				valueNew = dataGridViewCell->Style->NullValue;
			for each(DataGridViewCellValidator ^dataGridViewCellValidator in validators)
				if (!(errorText = dataGridViewCellValidator->Execute(dataGridViewCell, valueNew))->Equals(String::Empty))
					break;
		}
		else
			if (dataGridViewCell->Style->IsNullValueDefault)
				errorText = "Hodnota nie je inicializovan·";
		dataGridViewCell->ErrorText = errorText;
	}

	System::Void CheckUniqueDataGridViewCellValidator(DataGridViewCellValidator ^dataGridViewCellValidatorThis, DataGridViewCellValidator ^dataGridViewCellValidatorCompared, DataGridViewColumnValidators ^dataGridViewColumnValidators)
	{
		if (dataGridViewCellValidatorThis->GetType()->Equals(dataGridViewCellValidatorCompared->GetType()) && !dataGridViewCellValidatorThis->Equals(dataGridViewCellValidatorCompared))
			ThrowExc(String::Format("StÂpec '{0}' uû m· priraden˝ valid·tor typu '{1}'", dataGridViewColumnValidators->Column->Name, dataGridViewCellValidatorCompared->GetType()->Name));
	}

	System::Void DataGridViewCellValidator::Assign(DataGridViewValidator ^dataGridViewValidator, DataGridViewColumnValidators ^dataGridViewColumnValidators)
	{
		dataGridViewColumnValidators->Validators->Add(this);
	}

	System::Boolean DataGridViewCellValidator::Equals(Object ^obj)
	{
		return Object::Equals(obj) || (obj && this->GetType()->Equals(obj->GetType()));
	}

	System::Boolean DataGridViewCellValidator::IsConflicted(DataGridViewCellValidator ^dataGridViewCellValidatorCompared, DataGridViewColumnValidators ^dataGridViewColumnValidators)
	{
		return this->Equals(dataGridViewCellValidatorCompared);
	}

	System::String^ DataGridViewCellValidatorDesiredType::Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew)
	{
		if (valueNew->Equals(String::Empty))
			valueNew = DBNull::Value;
		String ^nullValue = String::Empty;
		if (!Convert::IsDBNull(valueNew) && dataGridViewCell->OwningColumn->ValueType != valueNew->GetType())
			if (dataGridViewCell->OwningColumn->ValueType == Int32::typeid)
			{
				Int32 value;
				String ^strValueNew = valueNew->ToString();
				if (Int32::TryParse(strValueNew, value))
					valueNew = value;
				else
					nullValue = strValueNew;
			}
			else if (dataGridViewCell->OwningColumn->ValueType == Boolean::typeid)
			{
				Boolean value;
				String ^strValueNew = valueNew->ToString();
				if (Boolean::TryParse(strValueNew, value))
					valueNew = value;
				else
					nullValue = strValueNew;
			}
		dataGridViewCell->Style->NullValue = nullValue;
		if (!dataGridViewCell->Style->IsNullValueDefault)
		{
			valueNew = DBNull::Value;
			return
				"Hodnota je v neplatnom tvare." + System::Environment::NewLine +
				"MusÌ obsahovaù celÈ ËÌslo.";
		}
		return String::Empty;
	}

	//System::String^ DataGridViewCellValidatorMustEqual::Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew)
	//{
	//	if (!value->Equals(valueNew) &&
	//		(
	//			indexDataGridViewRow < 0
	//			||
	//			dataGridViewCell->RowIndex == indexDataGridViewRow
	//			||
	//			(indexDataGridViewRow == Int32::MaxValue && dataGridViewCell->RowIndex == dataGridViewCell->DataGridView->RowCount - 1 - skipLastRow))
	//		))
	//		return String::Format("PolÌËko musÌ {0}.", Convert::IsDBNull(value) ? "byù pr·zdne" : String::Format("maù hodnotu '{0}'", value));
	//	return String::Empty;
	//}

	System::String^ DataGridViewCellValidatorNotNull::Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew)
	{
		if (Convert::IsDBNull(valueNew)/* && dataGridViewCell->Style->IsNullValueDefault*/)
			return "PolÌËko musÌ byù vyplnenÈ.";
		return String::Empty;
	}

	System::Boolean DataGridViewCellValidatorSetDefNull::Equals(Object ^obj)
	{
		if (Object::Equals(obj))
			return true;
		if (DataGridViewCellValidator::Equals(obj))
			return this->defValue->Equals(static_cast<DataGridViewCellValidatorSetDefNull^>(obj)->defValue);
		return false;
	}

	System::String^ DataGridViewCellValidatorSetDefNull::Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew)
	{
		if (Convert::IsDBNull(valueNew))
			valueNew = defValue;
		return String::Empty;
	}

	System::Boolean DataGridViewCellValidatorSetDefNull::IsConflicted(DataGridViewCellValidator ^dataGridViewCellValidatorCompared, DataGridViewColumnValidators ^dataGridViewColumnValidators)
	{
		CheckUniqueDataGridViewCellValidator(this, dataGridViewCellValidatorCompared, dataGridViewColumnValidators);
		return DataGridViewCellValidator::IsConflicted(dataGridViewCellValidatorCompared, dataGridViewColumnValidators);
	}

	System::String^ DataGridViewCellValidatorTrim::Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew)
	{
		if (String ^strValue = dynamic_cast<String^>(valueNew))
		{
			if (arrKeyword->Length)
			{
				for each (String ^keyword in arrKeyword)
				{
					String ^strValueNew = String::Empty;
					Int32 startIndexOld = 0;
					Int32 startIndexNew;
					while ((startIndexNew = strValue->IndexOf(keyword, startIndexOld, StringComparison::OrdinalIgnoreCase)) >= 0)
					{
						strValueNew += strValue->Substring(startIndexOld, startIndexNew - startIndexOld)->Trim() + keyword;
						startIndexOld = startIndexNew + keyword->Length;
					}
					strValue = strValueNew + strValue->Substring(startIndexOld)->Trim();
				}
				valueNew = strValue;
			}
			else
				valueNew = strValue->Trim();
		}
		return String::Empty;
	}

	//System::String^ DataGridViewCellValidatorUnique::Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew)
	//{
	//	return String::Empty;
	//}

	System::Void DataGridViewCellValidatorRelate::Assign(DataGridViewValidator ^dataGridViewValidator, DataGridViewColumnValidators ^dataGridViewColumnValidators)
	{
		DataGridViewCellValidator::Assign(dataGridViewValidator, dataGridViewColumnValidators);
		skipLastRow = dataGridViewValidator->SkipLastRow;
		if (!isEventsAssigned)
		{
			DataGridView ^dataGridView = dataGridViewColumnValidators->Column->DataGridView;
			dataGridView->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &DataGridViewCellValidatorRelate::DataGridView_CellValueChanged);
			if (previousRowDiff > 0)
				dataGridView->RowsRemoved += gcnew System::Windows::Forms::DataGridViewRowsRemovedEventHandler(this, &DataGridViewCellValidatorRelate::DataGridView_RowsRemoved);
			isEventsAssigned = true;
		}
		listRelateDataGridViewColumnValidators.Add(dataGridViewColumnValidators);
	}

	System::Void DataGridViewCellValidatorRelate::ExecuteRelateDataGridViewColumnValidators(DataGridView ^dataGridView, Int32 indexRow)
	{
		if (indexRow >= dataGridView->RowCount - skipLastRow)
			return;
		DataGridViewRow ^dataGridViewRow = dataGridView->Rows[indexRow];
		for each (DataGridViewColumnValidators ^dataGridViewColumnValidators in listRelateDataGridViewColumnValidators)
		{
			DataGridViewCell ^dataGridViewCell = GetDataGridViewCell(dataGridViewRow, dataGridViewColumnValidators->Column);
			Object ^valueNew = dataGridViewCell->Value;
			dataGridViewColumnValidators->Execute(dataGridViewCell, valueNew);
			dataGridViewCell->Value = valueNew;
		}
	}

	System::Void DataGridViewCellValidatorRelate::DataGridView_CellValueChanged(System::Object ^sender, System::Windows::Forms::DataGridViewCellEventArgs ^e)
	{
		if (e->RowIndex < 0 || e->ColumnIndex != dataGridViewColumnRelate->Index)
			return;
		ExecuteRelateDataGridViewColumnValidators(safe_cast<DataGridView^>(sender), e->RowIndex + previousRowDiff);
	}

	System::Void DataGridViewCellValidatorRelate::DataGridView_RowsRemoved(System::Object ^sender, System::Windows::Forms::DataGridViewRowsRemovedEventArgs ^e)
	{
		ExecuteRelateDataGridViewColumnValidators(safe_cast<DataGridView^>(sender), e->RowIndex + previousRowDiff - 1);
	}

	System::Boolean DataGridViewCellValidatorRelate::Equals(Object ^obj)
	{
		if (Object::Equals(obj))
			return true;
		if (DataGridViewCellValidator::Equals(obj))
		{
			DataGridViewCellValidatorRelate ^dataGridViewCellValidatorRelate = static_cast<DataGridViewCellValidatorRelate^>(obj);
			return
				this->dataGridViewColumnRelate->Equals(dataGridViewCellValidatorRelate->dataGridViewColumnRelate) &&
				this->previousRowDiff.Equals(dataGridViewCellValidatorRelate->previousRowDiff);
		}
		return false;
	}

	System::String^ DataGridViewCellValidatorRelate::Execute(DataGridViewCell ^dataGridViewCell, Object ^%valueNew)
	{
		if (dataGridViewCell->RowIndex >= previousRowDiff)
			return Calc(dataGridViewCell->DataGridView[dataGridViewColumnRelate->Index, dataGridViewCell->RowIndex - previousRowDiff]->Value, valueNew);
		return String::Empty;
	}

	System::String^ DataGridViewCellValidatorRelate::GetMessage(String ^message)
	{
		return String::Format("Hodnota {0} ako hodnota stÂpca '{1}'", message, dataGridViewColumnRelate->HeaderText) + (previousRowDiff == 0 ? String::Empty : String::Format(" {0}. {1} riadku", previousRowDiff, previousRowDiff < 0 ? "nasleduj˙ceho" : "predch·dzaj˙ceho"));
	}

	//System::String^ DataGridViewCellValidatorEqual::Calc(Object ^valueRelate, Object ^%valueNew)
	//{
	//	if (valueRelate->Equals(valueNew) == negation)
	//		return GetMessage(String::Format("musÌ byù {0}", negation ? "in·" : "rovnak·"));
	//	return String::Empty;
	//}

	System::String^ DataGridViewCellValidatorRelateInt32::Calc(Object ^valueRelate, Object ^%valueNew)
	{
		if (!Convert::IsDBNull(valueNew))
			if (Int32 ^valueRelateInt32 = dynamic_cast<Int32^>(valueRelate))
				return Calc(*valueRelateInt32, safe_cast<Int32>(valueNew));
		return String::Empty;
	}

	System::String^ DataGridViewCellValidatorMustBeDiff::Calc(Int32 valueRelate, Int32 valueNew)
	{
		if ((diffValue == Int32::MinValue && valueRelate <= valueNew)
			||
			(diffValue == Int32::MaxValue && valueRelate >= valueNew)
			||
			(diffValue > Int32::MinValue && diffValue < Int32::MaxValue && valueNew - valueRelate != diffValue))
			return GetMessage(String::Format("musÌ byù {0}", diffValue == 0 ? "rovnak·" : (((diffValue == Int32::MinValue || diffValue == Int32::MaxValue) ? String::Empty : String::Format("o {0} ", Math::Abs(diffValue))) + (diffValue < 0 ? "menöia" : "v‰Ëöia"))));
		return String::Empty;
	}

	System::Boolean DataGridViewCellValidatorMustBeDiff::Equals(Object ^obj)
	{
		if (Object::Equals(obj))
			return true;
		if (DataGridViewCellValidatorRelate::Equals(obj))
			return this->diffValue.Equals(static_cast<DataGridViewCellValidatorMustBeDiff^>(obj)->diffValue);
		return false;	
	}

	System::Boolean DataGridViewCellValidatorMustBeDiff::IsConflicted(DataGridViewCellValidator ^dataGridViewCellValidatorCompared, DataGridViewColumnValidators ^dataGridViewColumnValidators)
	{
		CheckUniqueDataGridViewCellValidator(this, dataGridViewCellValidatorCompared, dataGridViewColumnValidators);
		return DataGridViewCellValidatorRelate::IsConflicted(dataGridViewCellValidatorCompared, dataGridViewColumnValidators);
	}

	//System::String^ DataGridViewCellValidatorMustBeGreater::Calc(Int32 valueRelate, Int32 valueNew)
	//{
	//	if (valueRelate >= valueNew)
	//		return GetMessage("musÌ byù v‰Ëöia");
	//	return String::Empty;
	//}

	System::String^ DataGridViewCellValidatorNotLess::Calc(Int32 valueRelate, Int32 valueNew)
	{
		if (valueRelate > valueNew)
			return GetMessage("nesmie byù menöia");
		return String::Empty;
	}

	System::String^ DataGridViewCellValidatorSetDiff::Calc(Object ^valueRelate, Object ^%valueNew)
	{
		if (Int32 ^valueRelateInt32 = dynamic_cast<Int32^>(valueRelate))
			valueNew = *valueRelateInt32 + diffValue;
		else
			valueNew = DBNull::Value;
		return String::Empty;
	}

	//NumericUpDownEditingControl::NumericUpDownEditingControl()
	//{
	//	this->Minimum = 0;
	//	this->DecimalPlaces = 0;
	//	this->Maximum = 100;
	//}

	System::Windows::Forms::Cursor^ NumericUpDownEditingControl::EditingControlCursor::get()
	{
		return NumericUpDown::Cursor;
	}

	DataGridView^ NumericUpDownEditingControl::EditingControlDataGridView::get()
	{
		return dataGridViewControl;
	}

	Void NumericUpDownEditingControl::EditingControlDataGridView::set(DataGridView ^value)
	{
		dataGridViewControl = value;
	}

	Object^ NumericUpDownEditingControl::EditingControlFormattedValue::get()
	{
		return this->GetEditingControlFormattedValue(DataGridViewDataErrorContexts::Formatting);
	}

	Void NumericUpDownEditingControl::EditingControlFormattedValue::set(Object ^value)
	{
		if (Decimal ^valueDecimal = dynamic_cast<Decimal^>(value))
			valueOld = *valueDecimal;
		else if (Int32 ^valueInt32 = dynamic_cast<Int32^>(value))
			valueOld = *valueInt32;
		else if (String ^valueString = dynamic_cast<String^>(value))
			valueOld = Decimal::Parse(valueString);
		else
			valueOld = this->Minimum;
		this->Value = valueOld;
	}

	Int32 NumericUpDownEditingControl::EditingControlRowIndex::get()
	{
		return indexRow;
	}

	Void NumericUpDownEditingControl::EditingControlRowIndex::set(Int32 value)
	{
		indexRow = value;
	}

	Boolean NumericUpDownEditingControl::EditingControlValueChanged::get()
	{
		return this->Value != valueOld;
	}

	Void NumericUpDownEditingControl::EditingControlValueChanged::set(Boolean value)
	{
		valueOld = this->Value;
	}

	System::Windows::Forms::Cursor^ NumericUpDownEditingControl::EditingPanelCursor::get()
	{
		return this->EditingControlCursor;
	}

	Boolean NumericUpDownEditingControl::RepositionEditingControlOnValueChange::get()
	{
		return false;
	}

	Void NumericUpDownEditingControl::ApplyCellStyleToEditingControl(DataGridViewCellStyle ^dataGridViewCellStyle)
	{
		//this->Font = dataGridViewCellStyle->Font;
		//this->ForeColor = dataGridViewCellStyle->ForeColor;
		//this->BackColor = dataGridViewCellStyle->BackColor;
	}

	Boolean NumericUpDownEditingControl::EditingControlWantsInputKey(Keys key, Boolean dataGridViewWantsInputKey)
	{
		// todo: oöetriù stavy ako: ---1; 1-2; 5--; ----; 1,,,,1; ,,,; ,-,-,-; popup->"Prilepiù" hocijak˝ text
		//switch (key & Keys::KeyCode)
		//{
		//	case Keys::Escape:
		//		this->Value = valueOld;
		//	case Keys::Left:
		//	case Keys::Up:
		//	case Keys::Down:
		//	case Keys::Right:
		//	case Keys::Home:
		//	case Keys::End:
		//	case Keys::PageDown:
		//	case Keys::PageUp:
		//	case Keys::Enter:
		//		return true;
		//	default:
		//		return false;
		//}
		if ((key & Keys::KeyCode) == Keys::Escape)
			this->Value = valueOld;
		return true;
	}

	Object^ NumericUpDownEditingControl::GetEditingControlFormattedValue(DataGridViewDataErrorContexts context)
	{		
		return this->Text;
	}

	Void NumericUpDownEditingControl::OnValidated(EventArgs ^eventArgs)
	{
		this->EditingControlDataGridView->NotifyCurrentCellDirty(this->EditingControlValueChanged);
		NumericUpDown::OnValidated(eventArgs);
		if (this->EditingControlDataGridView->IsCurrentCellDirty)
			this->EditingControlDataGridView->CommitEdit(DataGridViewDataErrorContexts::Commit);
	}

	Void NumericUpDownEditingControl::PrepareEditingControlForEdit(Boolean selectAll)
	{
		if (selectAll)
			this->Select(0, this->Text->Length);
	}

	NumericUpDownCell::NumericUpDownCell()
	{
		this->Style->Format = "0";
	}

	//Object^ NumericUpDownCell::DefaultNewRowValue::get()
	//{
	//	return 0;
	//}

	Type^ NumericUpDownCell::EditType::get()
	{
		return NumericUpDownEditingControl::typeid;
	}

	Type^ NumericUpDownCell::ValueType::get()
	{
		return Int32::typeid;
	}

	Void NumericUpDownCell::InitializeEditingControl(Int32 rowIndex, Object ^initialFormattedValue, DataGridViewCellStyle ^dataGridViewCellStyle)
	{
		DataGridViewTextBoxCell::InitializeEditingControl(rowIndex, initialFormattedValue, dataGridViewCellStyle);
		safe_cast<NumericUpDownEditingControl^>(this->DataGridView->EditingControl)->EditingControlFormattedValue = this->Value;
	}

	DataGridViewCell^ DataGridViewNumericUpDownColumn::CellTemplate::get()
	{
		return DataGridViewColumn::CellTemplate;
	}

	Void DataGridViewNumericUpDownColumn::CellTemplate::set(DataGridViewCell ^value)
	{
		if ((value != nullptr) && !value->GetType()->IsAssignableFrom(NumericUpDownCell::typeid))
			throw gcnew InvalidCastException("Must be a NumericUpDownCell");
		DataGridViewColumn::CellTemplate = value;
	}

	String^ SqlValueOf(String ^value)
	{
		return "'" + value->Replace("'", "''") + "'";
	}

	String^ SqlValueOf(Double ^value)
	{
		return value->ToString(System::Globalization::CultureInfo::InvariantCulture);
	}

	String^ SqlValueOf(DateTime value)
	{
		return SqlValueOf(value.ToString("yyyy-MM-dd HH:mm:ss"));
	}

	String^ SqlValueOf(Object ^value)
	{
		return
			(!value || Convert::IsDBNull(value)) ? "NULL" :
			(dynamic_cast<String^>(value) ? SqlValueOf(static_cast<String^>(value)) :
			(dynamic_cast<Boolean^>(value) ? SqlValueOf(Convert::ToInt32(value)) :
			(dynamic_cast<Double^>(value) ? SqlValueOf(static_cast<Double^>(value)) :
			(dynamic_cast<DateTime^>(value) ? SqlValueOf(static_cast<DateTime>(value)) :
			value->ToString()))));
	}

	String^ SqlValueOf(DataGridViewCell ^value)
	{
		return SqlValueOf(value->Value);
	}

	Boolean Statics::IsNull(DateTime value)
	{
		return value == nullDateTime;
	}

	//System::Void Statics::dataGridViewInt_SortCompare(System::Object ^sender, System::Windows::Forms::DataGridViewSortCompareEventArgs ^e)
	//{
	//	if (e->Column->ValueType == Int32::typeid)
	//	{
	//		if (Convert::IsDBNull(e->CellValue1))
	//		{
	//			if (!Convert::IsDBNull(e->CellValue2))
	//				e->SortResult = -1;
	//			e->Handled = true;
	//		}
	//		else
	//			if (Convert::IsDBNull(e->CellValue2))
	//			{
	//				e->SortResult = 1;
	//				e->Handled = true;
	//			}
	//			else
	//			{
	//				Int32 intValue1;
	//				if (Int32::TryParse(e->CellValue1->ToString(), intValue1))
	//				{
	//					Int32 intValue2;
	//					if (Int32::TryParse(e->CellValue2->ToString(), intValue2))
	//					{
	//						e->SortResult = intValue1.CompareTo(intValue2);
	//						e->Handled = true;
	//					}
	//				}
	//			}
	//	}
	//}

	System::Void Statics::DataGridViewCellClickHeaderEndEdit(System::Object ^sender, System::Windows::Forms::DataGridViewCellEventArgs ^e)
	{
		if (e->RowIndex < 0)
			return;
		DataGridView ^dataGridView = safe_cast<DataGridView^>(sender);
		if (e->ColumnIndex < 0)
		{
			dataGridView->EditMode = DataGridViewEditMode::EditOnKeystrokeOrF2;
			dataGridView->EndEdit();
		}
		else
			dataGridView->EditMode = DataGridViewEditMode::EditOnEnter;
	}

	System::Void Statics::DataGridViewDataErrorThrowException(System::Object ^sender, System::Windows::Forms::DataGridViewDataErrorEventArgs ^e)
	{
		e->ThrowException = true;
	}

	System::Void Statics::DataGridViewUserDeletingRowConfirm(System::Object ^sender, System::Windows::Forms::DataGridViewRowCancelEventArgs ^e)
	{
		if (ShowMessageBox("SkutoËne chcete odstr·niù riadok?", MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::Yes)
			e->Cancel = true;
	}

	System::Void Statics::DataGridViewUserDeletingRowConfirmExceptLast(System::Object ^sender, System::Windows::Forms::DataGridViewRowCancelEventArgs ^e)
	{
		if (IsLastRow(e->Row))
			e->Cancel = true;
		else
			DataGridViewUserDeletingRowConfirm(sender, e);
	}

	DataGridViewCellEventHandler^ Statics::DataGridViewCellClickHeaderEndEditEventHandler::get()
	{
		if (!dataGridViewCellClickHeaderEndEditEventHandler)
			dataGridViewCellClickHeaderEndEditEventHandler = gcnew System::Windows::Forms::DataGridViewCellEventHandler(&Statics::DataGridViewCellClickHeaderEndEdit);
		return dataGridViewCellClickHeaderEndEditEventHandler;
	}

	DataGridViewDataErrorEventHandler^ Statics::DataGridViewDataErrorThrowExceptionEventHandler::get()
	{
		if (!dataGridViewDataErrorThrowExceptionEventHandler)
			dataGridViewDataErrorThrowExceptionEventHandler = gcnew System::Windows::Forms::DataGridViewDataErrorEventHandler(&Statics::DataGridViewDataErrorThrowException);
		return dataGridViewDataErrorThrowExceptionEventHandler;
	}

	DataGridViewRowCancelEventHandler^ Statics::DataGridViewUserDeletingRowConfirmEventHandler::get()
	{
		if (!dataGridViewUserDeletingRowConfirmEventHandler)
			dataGridViewUserDeletingRowConfirmEventHandler = gcnew System::Windows::Forms::DataGridViewRowCancelEventHandler(&Statics::DataGridViewUserDeletingRowConfirm);
		return dataGridViewUserDeletingRowConfirmEventHandler;
	}

	DataGridViewRowCancelEventHandler^ Statics::DataGridViewUserDeletingRowConfirmExceptLastEventHandler::get()
	{
		if (!dataGridViewUserDeletingRowConfirmExceptLastEventHandler)
			dataGridViewUserDeletingRowConfirmExceptLastEventHandler = gcnew System::Windows::Forms::DataGridViewRowCancelEventHandler(&Statics::DataGridViewUserDeletingRowConfirmExceptLast);
		return dataGridViewUserDeletingRowConfirmExceptLastEventHandler;
	}

	DataGridViewCellValidatorNotNull^ Statics::DataGridViewCellValidatorNotNullCommon::get()
	{
		if (!dataGridViewCellValidatorNotNullCommon)
			dataGridViewCellValidatorNotNullCommon = gcnew DataGridViewCellValidatorNotNull();
		return dataGridViewCellValidatorNotNullCommon;
	}

	DataGridViewCellValidatorTrim^ Statics::DataGridViewCellValidatorTrimCommon::get()
	{
		if (!dataGridViewCellValidatorTrimCommon)
			dataGridViewCellValidatorTrimCommon = gcnew DataGridViewCellValidatorTrim();
		return dataGridViewCellValidatorTrimCommon;
	}

	System::Drawing::Color Statics::ColorTextReadOnly::get()
	{
		return colorTextReadOnly;
	}

	KeyValueEmpty^ Statics::ItemKeyValueEmpty::get()
	{
		if (!itemKeyValueEmpty)
			itemKeyValueEmpty = gcnew KeyValueEmpty;
		return itemKeyValueEmpty;
	}

	DateTime Statics::NullDateTime::get()
	{
		return nullDateTime;
	}
}