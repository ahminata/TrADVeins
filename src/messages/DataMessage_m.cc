//
// Generated file, do not edit! Created by nedtool 4.6 from messages/DataMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "DataMessage_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(DataMessage);

DataMessage::DataMessage(const char *name, int kind) : ::cPacket(name,kind)
{
    this->message_id_var = 0;
    this->sender_id_var = 0;
    this->messageTTL_var = 0;
    this->messageOriginTime_var = 0;
    this->messageLength_var = 0;
    this->vecX_var = 0;
    this->vecY_var = 0;
    this->vecZ_var = 0;
    this->timestamp_var = 0;
}

DataMessage::DataMessage(const DataMessage& other) : ::cPacket(other)
{
    copy(other);
}

DataMessage::~DataMessage()
{
}

DataMessage& DataMessage::operator=(const DataMessage& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void DataMessage::copy(const DataMessage& other)
{
    this->message_id_var = other.message_id_var;
    this->sender_id_var = other.sender_id_var;
    this->messageOriginPosition_var = other.messageOriginPosition_var;
    this->messageTTL_var = other.messageTTL_var;
    this->messageOriginTime_var = other.messageOriginTime_var;
    this->messageLength_var = other.messageLength_var;
    this->vecX_var = other.vecX_var;
    this->vecY_var = other.vecY_var;
    this->vecZ_var = other.vecZ_var;
    this->timestamp_var = other.timestamp_var;
    this->liste_priority_trad_var = other.liste_priority_trad_var;
}

void DataMessage::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->message_id_var);
    doPacking(b,this->sender_id_var);
    doPacking(b,this->messageOriginPosition_var);
    doPacking(b,this->messageTTL_var);
    doPacking(b,this->messageOriginTime_var);
    doPacking(b,this->messageLength_var);
    doPacking(b,this->vecX_var);
    doPacking(b,this->vecY_var);
    doPacking(b,this->vecZ_var);
    doPacking(b,this->timestamp_var);
    doPacking(b,this->liste_priority_trad_var);
}

void DataMessage::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->message_id_var);
    doUnpacking(b,this->sender_id_var);
    doUnpacking(b,this->messageOriginPosition_var);
    doUnpacking(b,this->messageTTL_var);
    doUnpacking(b,this->messageOriginTime_var);
    doUnpacking(b,this->messageLength_var);
    doUnpacking(b,this->vecX_var);
    doUnpacking(b,this->vecY_var);
    doUnpacking(b,this->vecZ_var);
    doUnpacking(b,this->timestamp_var);
    doUnpacking(b,this->liste_priority_trad_var);
}

int DataMessage::getMessage_id() const
{
    return message_id_var;
}

void DataMessage::setMessage_id(int message_id)
{
    this->message_id_var = message_id;
}

int DataMessage::getSender_id() const
{
    return sender_id_var;
}

void DataMessage::setSender_id(int sender_id)
{
    this->sender_id_var = sender_id;
}

Coord& DataMessage::getMessageOriginPosition()
{
    return messageOriginPosition_var;
}

void DataMessage::setMessageOriginPosition(const Coord& messageOriginPosition)
{
    this->messageOriginPosition_var = messageOriginPosition;
}

simtime_t DataMessage::getMessageTTL() const
{
    return messageTTL_var;
}

void DataMessage::setMessageTTL(simtime_t messageTTL)
{
    this->messageTTL_var = messageTTL;
}

simtime_t DataMessage::getMessageOriginTime() const
{
    return messageOriginTime_var;
}

void DataMessage::setMessageOriginTime(simtime_t messageOriginTime)
{
    this->messageOriginTime_var = messageOriginTime;
}

int DataMessage::getMessageLength() const
{
    return messageLength_var;
}

void DataMessage::setMessageLength(int messageLength)
{
    this->messageLength_var = messageLength;
}

double DataMessage::getVecX() const
{
    return vecX_var;
}

void DataMessage::setVecX(double vecX)
{
    this->vecX_var = vecX;
}

double DataMessage::getVecY() const
{
    return vecY_var;
}

void DataMessage::setVecY(double vecY)
{
    this->vecY_var = vecY;
}

double DataMessage::getVecZ() const
{
    return vecZ_var;
}

void DataMessage::setVecZ(double vecZ)
{
    this->vecZ_var = vecZ;
}

simtime_t DataMessage::getTimestamp() const
{
    return timestamp_var;
}

void DataMessage::setTimestamp(simtime_t timestamp)
{
    this->timestamp_var = timestamp;
}

neighbors_rec& DataMessage::getListe_priority_trad()
{
    return liste_priority_trad_var;
}

void DataMessage::setListe_priority_trad(const neighbors_rec& liste_priority_trad)
{
    this->liste_priority_trad_var = liste_priority_trad;
}

class DataMessageDescriptor : public cClassDescriptor
{
  public:
    DataMessageDescriptor();
    virtual ~DataMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(DataMessageDescriptor);

DataMessageDescriptor::DataMessageDescriptor() : cClassDescriptor("DataMessage", "cPacket")
{
}

DataMessageDescriptor::~DataMessageDescriptor()
{
}

bool DataMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DataMessage *>(obj)!=NULL;
}

const char *DataMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DataMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount(object) : 11;
}

unsigned int DataMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<11) ? fieldTypeFlags[field] : 0;
}

const char *DataMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "message_id",
        "sender_id",
        "messageOriginPosition",
        "messageTTL",
        "messageOriginTime",
        "messageLength",
        "vecX",
        "vecY",
        "vecZ",
        "timestamp",
        "liste_priority_trad",
    };
    return (field>=0 && field<11) ? fieldNames[field] : NULL;
}

int DataMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "message_id")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sender_id")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageOriginPosition")==0) return base+2;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageTTL")==0) return base+3;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageOriginTime")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "messageLength")==0) return base+5;
    if (fieldName[0]=='v' && strcmp(fieldName, "vecX")==0) return base+6;
    if (fieldName[0]=='v' && strcmp(fieldName, "vecY")==0) return base+7;
    if (fieldName[0]=='v' && strcmp(fieldName, "vecZ")==0) return base+8;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestamp")==0) return base+9;
    if (fieldName[0]=='l' && strcmp(fieldName, "liste_priority_trad")==0) return base+10;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DataMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "Coord",
        "simtime_t",
        "simtime_t",
        "int",
        "double",
        "double",
        "double",
        "simtime_t",
        "neighbors_rec",
    };
    return (field>=0 && field<11) ? fieldTypeStrings[field] : NULL;
}

const char *DataMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int DataMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DataMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMessage_id());
        case 1: return long2string(pp->getSender_id());
        case 2: {std::stringstream out; out << pp->getMessageOriginPosition(); return out.str();}
        case 3: return double2string(pp->getMessageTTL());
        case 4: return double2string(pp->getMessageOriginTime());
        case 5: return long2string(pp->getMessageLength());
        case 6: return double2string(pp->getVecX());
        case 7: return double2string(pp->getVecY());
        case 8: return double2string(pp->getVecZ());
        case 9: return double2string(pp->getTimestamp());
        case 10: {std::stringstream out; out << pp->getListe_priority_trad(); return out.str();}
        default: return "";
    }
}

bool DataMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setMessage_id(string2long(value)); return true;
        case 1: pp->setSender_id(string2long(value)); return true;
        case 3: pp->setMessageTTL(string2double(value)); return true;
        case 4: pp->setMessageOriginTime(string2double(value)); return true;
        case 5: pp->setMessageLength(string2long(value)); return true;
        case 6: pp->setVecX(string2double(value)); return true;
        case 7: pp->setVecY(string2double(value)); return true;
        case 8: pp->setVecZ(string2double(value)); return true;
        case 9: pp->setTimestamp(string2double(value)); return true;
        default: return false;
    }
}

const char *DataMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 2: return opp_typename(typeid(Coord));
        case 10: return opp_typename(typeid(neighbors_rec));
        default: return NULL;
    };
}

void *DataMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DataMessage *pp = (DataMessage *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getMessageOriginPosition()); break;
        case 10: return (void *)(&pp->getListe_priority_trad()); break;
        default: return NULL;
    }
}


