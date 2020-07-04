//
// Generated file, do not edit! Created by nedtool 4.6 from messages/BeaconMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BeaconMessage_m.h"

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

Register_Class(BeaconMessage);

BeaconMessage::BeaconMessage(const char *name, int kind) : ::cPacket(name,kind)
{
    this->carId_var = 0;
    this->nbr_neighbor_var = 0;
    this->speed_var = 0;
    this->angleRad_var = 0;
    this->vecX_var = 0;
    this->vecY_var = 0;
    this->vecZ_var = 0;
    this->cbr_var = 0;
}

BeaconMessage::BeaconMessage(const BeaconMessage& other) : ::cPacket(other)
{
    copy(other);
}

BeaconMessage::~BeaconMessage()
{
}

BeaconMessage& BeaconMessage::operator=(const BeaconMessage& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void BeaconMessage::copy(const BeaconMessage& other)
{
    this->carId_var = other.carId_var;
    this->nbr_neighbor_var = other.nbr_neighbor_var;
    this->position_var = other.position_var;
    this->speed_var = other.speed_var;
    this->angleRad_var = other.angleRad_var;
    this->vecX_var = other.vecX_var;
    this->vecY_var = other.vecY_var;
    this->vecZ_var = other.vecZ_var;
    this->cbr_var = other.cbr_var;
    this->liste_message_urgence_var = other.liste_message_urgence_var;
}

void BeaconMessage::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->carId_var);
    doPacking(b,this->nbr_neighbor_var);
    doPacking(b,this->position_var);
    doPacking(b,this->speed_var);
    doPacking(b,this->angleRad_var);
    doPacking(b,this->vecX_var);
    doPacking(b,this->vecY_var);
    doPacking(b,this->vecZ_var);
    doPacking(b,this->cbr_var);
    doPacking(b,this->liste_message_urgence_var);
}

void BeaconMessage::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->carId_var);
    doUnpacking(b,this->nbr_neighbor_var);
    doUnpacking(b,this->position_var);
    doUnpacking(b,this->speed_var);
    doUnpacking(b,this->angleRad_var);
    doUnpacking(b,this->vecX_var);
    doUnpacking(b,this->vecY_var);
    doUnpacking(b,this->vecZ_var);
    doUnpacking(b,this->cbr_var);
    doUnpacking(b,this->liste_message_urgence_var);
}

int BeaconMessage::getCarId() const
{
    return carId_var;
}

void BeaconMessage::setCarId(int carId)
{
    this->carId_var = carId;
}

int BeaconMessage::getNbr_neighbor() const
{
    return nbr_neighbor_var;
}

void BeaconMessage::setNbr_neighbor(int nbr_neighbor)
{
    this->nbr_neighbor_var = nbr_neighbor;
}

Coord& BeaconMessage::getPosition()
{
    return position_var;
}

void BeaconMessage::setPosition(const Coord& position)
{
    this->position_var = position;
}

double BeaconMessage::getSpeed() const
{
    return speed_var;
}

void BeaconMessage::setSpeed(double speed)
{
    this->speed_var = speed;
}

double BeaconMessage::getAngleRad() const
{
    return angleRad_var;
}

void BeaconMessage::setAngleRad(double angleRad)
{
    this->angleRad_var = angleRad;
}

double BeaconMessage::getVecX() const
{
    return vecX_var;
}

void BeaconMessage::setVecX(double vecX)
{
    this->vecX_var = vecX;
}

double BeaconMessage::getVecY() const
{
    return vecY_var;
}

void BeaconMessage::setVecY(double vecY)
{
    this->vecY_var = vecY;
}

double BeaconMessage::getVecZ() const
{
    return vecZ_var;
}

void BeaconMessage::setVecZ(double vecZ)
{
    this->vecZ_var = vecZ;
}

double BeaconMessage::getCbr() const
{
    return cbr_var;
}

void BeaconMessage::setCbr(double cbr)
{
    this->cbr_var = cbr;
}

urgent_message_rec& BeaconMessage::getListe_message_urgence()
{
    return liste_message_urgence_var;
}

void BeaconMessage::setListe_message_urgence(const urgent_message_rec& liste_message_urgence)
{
    this->liste_message_urgence_var = liste_message_urgence;
}

class BeaconMessageDescriptor : public cClassDescriptor
{
  public:
    BeaconMessageDescriptor();
    virtual ~BeaconMessageDescriptor();

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

Register_ClassDescriptor(BeaconMessageDescriptor);

BeaconMessageDescriptor::BeaconMessageDescriptor() : cClassDescriptor("BeaconMessage", "cPacket")
{
}

BeaconMessageDescriptor::~BeaconMessageDescriptor()
{
}

bool BeaconMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BeaconMessage *>(obj)!=NULL;
}

const char *BeaconMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BeaconMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount(object) : 10;
}

unsigned int BeaconMessageDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *BeaconMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "carId",
        "nbr_neighbor",
        "position",
        "speed",
        "angleRad",
        "vecX",
        "vecY",
        "vecZ",
        "cbr",
        "liste_message_urgence",
    };
    return (field>=0 && field<10) ? fieldNames[field] : NULL;
}

int BeaconMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "carId")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nbr_neighbor")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "position")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "speed")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "angleRad")==0) return base+4;
    if (fieldName[0]=='v' && strcmp(fieldName, "vecX")==0) return base+5;
    if (fieldName[0]=='v' && strcmp(fieldName, "vecY")==0) return base+6;
    if (fieldName[0]=='v' && strcmp(fieldName, "vecZ")==0) return base+7;
    if (fieldName[0]=='c' && strcmp(fieldName, "cbr")==0) return base+8;
    if (fieldName[0]=='l' && strcmp(fieldName, "liste_message_urgence")==0) return base+9;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BeaconMessageDescriptor::getFieldTypeString(void *object, int field) const
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
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
        "urgent_message_rec",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : NULL;
}

const char *BeaconMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int BeaconMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BeaconMessage *pp = (BeaconMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BeaconMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BeaconMessage *pp = (BeaconMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCarId());
        case 1: return long2string(pp->getNbr_neighbor());
        case 2: {std::stringstream out; out << pp->getPosition(); return out.str();}
        case 3: return double2string(pp->getSpeed());
        case 4: return double2string(pp->getAngleRad());
        case 5: return double2string(pp->getVecX());
        case 6: return double2string(pp->getVecY());
        case 7: return double2string(pp->getVecZ());
        case 8: return double2string(pp->getCbr());
        case 9: {std::stringstream out; out << pp->getListe_message_urgence(); return out.str();}
        default: return "";
    }
}

bool BeaconMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BeaconMessage *pp = (BeaconMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setCarId(string2long(value)); return true;
        case 1: pp->setNbr_neighbor(string2long(value)); return true;
        case 3: pp->setSpeed(string2double(value)); return true;
        case 4: pp->setAngleRad(string2double(value)); return true;
        case 5: pp->setVecX(string2double(value)); return true;
        case 6: pp->setVecY(string2double(value)); return true;
        case 7: pp->setVecZ(string2double(value)); return true;
        case 8: pp->setCbr(string2double(value)); return true;
        default: return false;
    }
}

const char *BeaconMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 2: return opp_typename(typeid(Coord));
        case 9: return opp_typename(typeid(urgent_message_rec));
        default: return NULL;
    };
}

void *BeaconMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BeaconMessage *pp = (BeaconMessage *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getPosition()); break;
        case 9: return (void *)(&pp->getListe_message_urgence()); break;
        default: return NULL;
    }
}


