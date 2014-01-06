// Author: Alireza Khatamian

#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "../../../includes/FileSet/PdbFileSpace/pdbfile.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbheadercard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbtitlecard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbcompoundcard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbnummodelcard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbmodeltypecard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbresiduesequence.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbresiduemodificationcard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbheterogencard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbheterogennamecard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbheterogensynonymcard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbformula.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbhelixcard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbsheetcard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbdisulfidebondcard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdblinkcard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbsitecard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbcrystallographiccard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdboriginxncard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbscalencard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbmatrixncard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbmodelcard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbconnectcard.hpp"
#include "../../../includes/FileSet/PdbFileSpace/pdbfileprocessingexception.hpp"
#include "../../../includes/utils.hpp"

using namespace std;
using namespace PdbFileSpace;
using namespace gmml;

//////////////////////////////////////////////////////////
//                       CONSTRUCTOR                    //
//////////////////////////////////////////////////////////
PdbFile::PdbFile(const std::string &pdb_file)
{
    path_ = pdb_file;
    std::ifstream in_file;
    try
    {
        in_file.open(pdb_file.c_str());
    }
    catch(...)
    {
        throw PdbFileProcessingException(__LINE__,"File not found");
    }
    Read(in_file);
    in_file.close();            /// Close the parameter files
}

//////////////////////////////////////////////////////////
//                         ACCESSOR                     //
//////////////////////////////////////////////////////////
string PdbFile::GetPath()
{
    return path_;
}

PdbHeaderCard* PdbFile::GetHeader()
{
    return header_;
}

PdbTitleCard* PdbFile::GetTitle()
{
    return title_;
}

PdbCompoundCard* PdbFile::GetCompound()
{
    return compound_;
}

PdbNumModelCard* PdbFile::GetNumberOfModels()
{
    return number_of_models_;
}

PdbModelTypeCard* PdbFile::GetModelType()
{
    return model_type_;
}

PdbResidueSeqenceCard* PdbFile::GetResidueSequence()
{
    return residues_sequence_;
}

PdbResidueModificationCard* PdbFile::GetResidueModification()
{
    return residue_modification_;
}

PdbHeterogenCard* PdbFile::GetHeterogens()
{
    return heterogens_;
}

PdbHeterogenNameCard* PdbFile::GetHeterogensName()
{
    return heterogens_name_;
}

PdbHeterogenSynonymCard* PdbFile::GetHeterogenSynonyms()
{
    return heterogen_synonyms_;
}

PdbFormulaCard* PdbFile::GetFormulas()
{
    return formulas_;
}

PdbHelixCard* PdbFile::GetHelixes()
{
    return helixes_;
}

PdbSheetCard* PdbFile::GetSheets()
{
    return sheets_;
}

PdbDisulfideBondCard* PdbFile::GetDisulfideBonds()
{
    return disulfide_bonds_;
}

PdbLinkCard* PdbFile::GetLinks()
{
    return links_;
}

PdbSiteCard* PdbFile::GetSites()
{
    return sites_;
}

PdbCrystallographicCard* PdbFile::GetCrystallography()
{
    return crystallography_;
}

PdbOriginXnCard* PdbFile::GetOrigins()
{
    return origins_;
}

PdbScaleNCard* PdbFile::GetScales()
{
    return scales_;
}

PdbMatrixNCard* PdbFile::GetMatrices()
{
    return matrices_;
}

PdbModelCard* PdbFile::GetModels()
{
    return models_;
}

PdbConnectCard* PdbFile::GetConnectivities()
{
    return connectivities_;
}

//////////////////////////////////////////////////////////
//                          MUTATOR                     //
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
//                        FUNCTIONS                     //
//////////////////////////////////////////////////////////
void PdbFile::Read(ifstream &in_file)
{
    this->ParseCards(in_file);
}

void PdbFile::ParseCards(ifstream &in_stream)
{
    string line;

    /// Unable to read file
    if (!getline(in_stream, line))
    {
        throw PdbFileProcessingException("Error reading file");
    }

    string record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "HEADER")
    {
        ParseHeaderCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "OBSLTE")
    {
        ParseObsoleteCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "TITLE")
    {
        ParseTitleCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "SPLIT")
    {
        ParseSplitCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "CAVEAT")
    {
        ParseCaveatCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "COMPND")
    {        
        ParseCompoundCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "SOURCE")
    {
        ParseSourceCard(in_stream, line);
    }
    cout << line << endl;
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "KEYWDS")
    {
        ParseKeywordCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "EXPDTA")
    {
        ParseExpirationDateCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "NUMMDL")
    {
        cout << "HERE" << endl;
        ParseNumModelCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "MDLTYP")
    {
        ParseModelTypeCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "AUTHOR")
    {
        ParseAuthorCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "REVDAT")
    {
        ParseRevisionDateCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "SPRSDE")
    {
        ParseSupersededEntriesCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "JRNL")
    {
        ParseJournalCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "REMARK")
    {
        ParseRemarkCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name.find("DBREF") != string::npos)
    {
        ParseDatabaseReferenceCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "SEQADV")
    {
        ParseSequenceAdvancedCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "SEQRES")
    {
        ParseSequenceResidueCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "MODRES")
    {
        ParseModificationResidueCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "HET")
    {
        ParseHeterogenCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "HETNAM")
    {
        ParseHeterogenNameCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "HETSYN")
    {
        ParseHeterogenSynonymCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "FORMUL")
    {
        ParseFormulaCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "HELIX")
    {
        ParseHelixCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "SHEET")
    {
        ParseSheetCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "SSBOND")
    {
        ParseDisulfideBondCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "LINK")
    {
        ParseLinkCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "CISPEP")
    {
        ParseCISPeptideCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "SITE")
    {
        ParseSiteCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "CRYST1")
    {
        ParseCrystallographyCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name.find("ORIGX") != string::npos)
    {
        ParseOriginCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name.find("SCALE") != string::npos)
    {
        ParseScaleCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name.find("MTRIX") != string::npos)
    {
        ParseMatrixCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "MODEL")
    {
        ParseModelCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "CONECT")
    {
        ParseConnectivityCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "MASTER")
    {
        ParseMasterCard(in_stream, line);
    }
    record_name = line.substr(0,6);
    record_name = Trim(record_name);
    if(record_name == "END")
    {
        ParseEndCard(in_stream, line);
    }
}

void PdbFile::ParseHeaderCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "HEADER")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

    header_ = new PdbHeaderCard(stream_block);
    cout << header_->GetRecordName() << "\t" << header_->GetClassification() << "\t" << header_->GetDepositionDate() << "\t" << header_->GetIdentifierCode() << endl;
}

void PdbFile::ParseObsoleteCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "OBSLTE")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseTitleCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "TITLE")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

    title_ = new PdbTitleCard(stream_block);
    cout << title_->GetRecordName() << "\t" << title_->GetTitle() << endl;
}

void PdbFile::ParseSplitCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "SPLIT")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseCaveatCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "CAVEAT")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseCompoundCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "COMPND")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    compound_ = new PdbCompoundCard(stream_block);
}

void PdbFile::ParseSourceCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "SOURCE")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseKeywordCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "KEYWDS")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseExpirationDateCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "EXPDTA")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseNumModelCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "NUMMDL")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

    number_of_models_ = new PdbNumModelCard(stream_block);
    cout << number_of_models_->GetRecordName() << number_of_models_->GetNumberOfModels() << endl;
}

void PdbFile::ParseModelTypeCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "MDLTYP")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

    model_type_ = new PdbModelTypeCard(stream_block);
    cout << model_type_->GetRecordName() << endl;
    for(vector<string>::iterator it = model_type_->GetComments().begin(); it != model_type_->GetComments().end(); it++)
    {
        cout << (*it) << endl;
    }
}

void PdbFile::ParseAuthorCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "AUTHOR")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseRevisionDateCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "REVDAT")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseSupersededEntriesCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "SPRSDE")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseJournalCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "JRNL")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseRemarkCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "REMARK")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseDatabaseReferenceCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "DBREF")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseSequenceAdvancedCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "SEQADV")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseSequenceResidueCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "SEQRES")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    residues_sequence_ = new PdbResidueSeqenceCard(stream_block);
}

void PdbFile::ParseModificationResidueCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "MODRES")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    residue_modification_ = new PdbResidueModificationCard(stream_block);
}

void PdbFile::ParseHeterogenCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "HET")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    heterogens_ = new PdbHeterogenCard(stream_block);
}

void PdbFile::ParseHeterogenNameCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "HETNAM")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    heterogens_name_ = new PdbHeterogenNameCard(stream_block);
}

void PdbFile::ParseHeterogenSynonymCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "HETSYN")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    heterogen_synonyms_ = new PdbHeterogenSynonymCard(stream_block);
}

void PdbFile::ParseFormulaCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "FORMUL")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    formulas_ = new PdbFormulaCard(stream_block);
}

void PdbFile::ParseHelixCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "HELIX")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    helixes_ = new PdbHelixCard(stream_block);
}

void PdbFile::ParseSheetCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "SHEET")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    sheets_ = new PdbSheetCard(stream_block);
}

void PdbFile::ParseDisulfideBondCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "SSBOND")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    disulfide_bonds_ = new PdbDisulfideBondCard(stream_block);
}

void PdbFile::ParseLinkCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "LINK")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    links_ = new PdbLinkCard(stream_block);
}

void PdbFile::ParseCISPeptideCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "CISPEP")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseSiteCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "SITE")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    sites_ = new PdbSiteCard(stream_block);
}

void PdbFile::ParseCrystallographyCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "CRYST1")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

    crystallography_ = new PdbCrystallographicCard(stream_block);
    cout << crystallography_->GetRecordName() << "\t" << crystallography_->GetA() << "\t" << crystallography_->GetB() << "\t" << crystallography_->GetC() << "\t" <<
            crystallography_->GetAlpha() << "\t" << crystallography_->GetBeta() << "\t" << crystallography_->GetGamma() << "\t" <<
            crystallography_->GetSpaceGroup() << "\t" << crystallography_->GetZValue() << endl;
}

void PdbFile::ParseOriginCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,5);
    record_name = Trim(record_name);

    while(record_name == "ORIGX")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    origins_ = new PdbOriginXnCard(stream_block);
}

void PdbFile::ParseScaleCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,5);
    record_name = Trim(record_name);

    while(record_name == "SCALE")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    scales_ = new PdbScaleNCard(stream_block);
}

void PdbFile::ParseMatrixCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,5);
    record_name = Trim(record_name);

    while(record_name == "MTRIX")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    matrices_ = new PdbMatrixNCard(stream_block);
}

void PdbFile::ParseModelCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "MODEL" || record_name == "ATOM" || record_name == "ANISOU"
          || record_name == "TER" || record_name == "HETATM" || record_name == "ENDMDL" )
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    heterogens_name_ = new PdbHeterogenNameCard(stream_block);
}

void PdbFile::ParseConnectivityCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "CONECT")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }

//    connectivities_ = new PdbConnectCard(stream_block);
}

void PdbFile::ParseMasterCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "MASTER")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

void PdbFile::ParseEndCard(std::ifstream& stream, string& line)
{
    stringstream stream_block;
    stream_block << line << endl;
    getline(stream, line);
    string record_name = line.substr(0,6);
    record_name = Trim(record_name);

    while(record_name == "END")
    {
        stream_block << line << endl;
        getline(stream, line);
        record_name = line.substr(0,6);
        record_name = Trim(record_name);
    }
}

//////////////////////////////////////////////////////////
//                      DISPLAY FUNCTION                //
//////////////////////////////////////////////////////////

