#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "domain/Address.h"
#include "domain/Alias.h"
#include "domain/BirthYear.h"
#include "domain/ChangeRecord.h"
#include "domain/Gender.h"
#include "domain/Person.h"
#include "domain/Relationship.h"
#include "domain/RelationshipMetadata.h"
#include "domain/RelationshipStrength.h"
#include "domain/Religion.h"
#include "domain/SexualOrientation.h"
#include "domain/ThreatInfo.h"

// NOLINTBEGIN(readability-identifier-length, *-pro-bounds-avoid-unchecked-container-access)

// --- Timestamp helpers ---
// nlohmann resolves converters via ADL, searching namespaces associated with
// the type. std::chrono::time_point lives in std::chrono, which nlohmann never
// searches. Explicit helpers bypass ADL entirely.

inline int64_t tpToJson(const std::chrono::system_clock::time_point &tp) {
    return std::chrono::system_clock::to_time_t(tp);
}

inline std::chrono::system_clock::time_point tpFromJson(const nlohmann::json &j) {
    return std::chrono::system_clock::from_time_t(j.get<int64_t>());
}


// --- Enums ---

NLOHMANN_JSON_SERIALIZE_ENUM(Gender, {
                             {Gender::Male, "Male"},
                             {Gender::Female, "Female"},
                             {Gender::Unspecified, "Unspecified"},
                             })

NLOHMANN_JSON_SERIALIZE_ENUM(SexualOrientation, {
                             {SexualOrientation::Hetero, "Hetero"},
                             {SexualOrientation::Homo, "Homo"},
                             {SexualOrientation::Bisexual, "Bisexual"},
                             {SexualOrientation::Other, "Other"},
                             {SexualOrientation::Unknown, "Unknown"},
                             })

NLOHMANN_JSON_SERIALIZE_ENUM(ReligionType, {
                             {ReligionType::None, "None"},
                             {ReligionType::Atheism, "Atheism"},
                             {ReligionType::Christianity, "Christianity"},
                             {ReligionType::Islam, "Islam"},
                             {ReligionType::Buddhism, "Buddhism"},
                             {ReligionType::Hinduism, "Hinduism"},
                             {ReligionType::Judaism, "Judaism"},
                             {ReligionType::Other, "Other"},
                             {ReligionType::Unknown, "Unknown"},
                             })

NLOHMANN_JSON_SERIALIZE_ENUM(AddressType, {
                             {AddressType::Home, "Home"},
                             {AddressType::Work, "Work"},
                             {AddressType::School, "School"},
                             {AddressType::Gym, "Gym"},
                             {AddressType::Verein, "Verein"},
                             {AddressType::Other, "Other"},
                             })

NLOHMANN_JSON_SERIALIZE_ENUM(ChangeType, {
                             {ChangeType::FieldModified, "FieldModified"},
                             {ChangeType::NoteAdded, "NoteAdded"},
                             })

NLOHMANN_JSON_SERIALIZE_ENUM(RelationshipTier, {
                             {RelationshipTier::HeardOf, "HeardOf"},
                             {RelationshipTier::Acquaintance, "Acquaintance"},
                             {RelationshipTier::Colleague, "Colleague"},
                             {RelationshipTier::Friend, "Friend"},
                             {RelationshipTier::CloseFriend, "CloseFriend"},
                             {RelationshipTier::Intimate, "Intimate"},
                             {RelationshipTier::Family, "Family"},
                             })

NLOHMANN_JSON_SERIALIZE_ENUM(RelationshipType, {
                             {RelationshipType::KnowsOf, "KnowsOf"},
                             {RelationshipType::Acquaintance, "Acquaintance"},
                             {RelationshipType::Colleague, "Colleague"},
                             {RelationshipType::Friend, "Friend"},
                             {RelationshipType::Romantic, "Romantic"},
                             {RelationshipType::Family, "Family"},
                             {RelationshipType::Adversarial, "Adversarial"},
                             {RelationshipType::Other, "Other"},
                             })

NLOHMANN_JSON_SERIALIZE_ENUM(MeetingFrequency, {
                             {MeetingFrequency::Daily, "Daily"},
                             {MeetingFrequency::Weekly, "Weekly"},
                             {MeetingFrequency::Monthly, "Monthly"},
                             {MeetingFrequency::Occasionally, "Occasionally"},
                             {MeetingFrequency::Rarely, "Rarely"},
                             })

NLOHMANN_JSON_SERIALIZE_ENUM(EvidenceLevel, {
                             {EvidenceLevel::Assumed, "Assumed"},
                             {EvidenceLevel::Reported, "Reported"},
                             {EvidenceLevel::Observed, "Observed"},
                             {EvidenceLevel::Confirmed, "Confirmed"},
                             })


// --- Value types ---

inline void to_json(nlohmann::json &j, const BirthYear &b) {
    j["year"] = b.year();
    j["is_approximate"] = b.is_approximate();
}

inline void from_json(const nlohmann::json &j, BirthYear &b) {
    b = BirthYear{
        j.at("year").get<uint16_t>(),
        j.at("is_approximate").get<bool>()
    };
}

// ---

inline void to_json(nlohmann::json &j, const Alias &a) {
    j["name"] = a.name;
    j["is_primary"] = a.is_primary;
}

inline void from_json(const nlohmann::json &j, Alias &a) {
    a = Alias{
        .name = j.at("name").get<std::string>(),
        .is_primary = j.at("is_primary").get<bool>(),
    };
}

// ---

inline void to_json(nlohmann::json &j, const Address &a) {
    j["city"] = a.city;
    j["country"] = a.country;
    j["street"] = a.street;
}

inline void from_json(const nlohmann::json &j, Address &a) {
    a = Address{
        .city = j.at("city").get<std::string>(),
        .country = j.at("country").get<std::string>(),
        .street = j.at("street").get<std::optional<std::string> >(),
    };
}

// ---

inline void to_json(nlohmann::json &j, const TaggedAddress &a) {
    j["type"] = a.type;
    j["label"] = a.label;
    j["location"] = a.location;
    j["notes"] = a.notes;
}

inline void from_json(const nlohmann::json &j, TaggedAddress &a) {
    a = TaggedAddress{
        .type = j.at("type").get<AddressType>(),
        .label = j.at("label").get<std::optional<std::string> >(),
        .location = j.at("location").get<Address>(),
        .notes = j.at("notes").get<std::optional<std::string> >(),
    };
}

// ---

inline void to_json(nlohmann::json &j, const Religion &r) {
    j["observed"] = r.observed;
    j["actual"] = r.actual;
    j["other_label"] = r.other_label;
}

inline void from_json(const nlohmann::json &j, Religion &r) {
    r = Religion{
        .observed = j.at("observed").get<ReligionType>(),
        .actual = j.at("actual").get<std::optional<ReligionType> >(),
        .other_label = j.at("other_label").get<std::optional<std::string> >(),
    };
}

// ---

inline void to_json(nlohmann::json &j, const ChangeRecord &c) {
    j["timestamp"] = tpToJson(c.timestamp);
    j["type"] = c.type;
    j["field_name"] = c.field_name;
    j["old_value"] = c.old_value;
    j["new_value"] = c.new_value;
    j["note"] = c.note;
}

inline void from_json(const nlohmann::json &j, ChangeRecord &c) {
    c = ChangeRecord{
        .timestamp = tpFromJson(j.at("timestamp")),
        .type = j.at("type").get<ChangeType>(),
        .field_name = j.at("field_name").get<std::optional<std::string> >(),
        .old_value = j.at("old_value").get<std::optional<std::string> >(),
        .new_value = j.at("new_value").get<std::optional<std::string> >(),
        .note = j.at("note").get<std::optional<std::string> >(),
    };
}

// ---

inline void to_json(nlohmann::json &j, const ThreatInfo &t) {
    j["active"] = t.active;
    j["reason"] = t.reason;
}

inline void from_json(const nlohmann::json &j, ThreatInfo &t) {
    t = ThreatInfo{
        .active = j.at("active").get<bool>(),
        .reason = j.at("reason").get<std::string>(),
    };
}

// ---

inline void to_json(nlohmann::json &j, const RelationshipStrength &s) {
    j["tier"] = s.tier;
    j["intensity"] = s.intensity;
}

inline void from_json(const nlohmann::json &j, RelationshipStrength &s) {
    s = RelationshipStrength{
        .tier = j.at("tier").get<RelationshipTier>(),
        .intensity = j.at("intensity").get<uint8_t>(),
    };
}

// ---

inline void to_json(nlohmann::json &j, const RelationshipMetadata &m) {
    j["meeting_frequency"] = m.meeting_frequency;
    j["meeting_context"] = m.meeting_context;
    j["evidence_level"] = m.evidence_level;
    j["how_they_met"] = m.how_they_met;
}

inline void from_json(const nlohmann::json &j, RelationshipMetadata &m) {
    m = RelationshipMetadata{
        .meeting_frequency = j.at("meeting_frequency").get<std::optional<MeetingFrequency> >(),
        .meeting_context = j.at("meeting_context").get<std::optional<std::string> >(),
        .evidence_level = j.at("evidence_level").get<EvidenceLevel>(),
        .how_they_met = j.at("how_they_met").get<std::optional<std::string> >(),
    };
}


// --- Core domain types ---

inline void to_json(nlohmann::json &j, const Person &p) {
    j["id"] = p.id;
    j["first_name"] = p.first_name;
    j["surname"] = p.surname;
    j["aliases"] = p.aliases;
    j["gender"] = p.gender;
    j["birth_year"] = p.birth_year;
    j["sexual_orientation"] = p.sexual_orientation;
    j["religion"] = p.religion;
    j["addresses"] = p.addresses;
    j["notes"] = p.notes;
    j["created_at"] = tpToJson(p.created_at);
    j["change_history"] = p.change_history;
}

inline void from_json(const nlohmann::json &j, Person &p) {
    p.id = j.at("id").get<PersonId>();
    p.first_name = j.at("first_name").get<std::string>();
    p.surname = j.at("surname").get<std::optional<std::string> >();
    p.aliases = j.at("aliases").get<std::vector<Alias> >();
    p.gender = j.at("gender").get<Gender>();
    p.birth_year = j.at("birth_year").get<std::optional<BirthYear> >();
    p.sexual_orientation = j.at("sexual_orientation").get<std::optional<SexualOrientation> >();
    p.religion = j.at("religion").get<std::optional<Religion> >();
    p.addresses = j.at("addresses").get<std::vector<TaggedAddress> >();
    p.notes = j.at("notes").get<std::optional<std::string> >();
    p.created_at = tpFromJson(j.at("created_at"));
    p.change_history = j.at("change_history").get<std::vector<ChangeRecord> >();
}

// ---

inline void to_json(nlohmann::json &j, const Relationship &r) {
    j["id"] = r.id;
    j["from_id"] = r.from_id;
    j["to_id"] = r.to_id;
    j["type"] = r.type;
    j["type_label"] = r.type_label;
    j["strength"] = r.strength;
    j["my_relationship_role"] = r.my_relationship_role;
    j["is_active"] = r.is_active;
    j["threat_to_from"] = r.threat_to_from;
    j["threat_to_me"] = r.threat_to_me;
    j["metadata"] = r.metadata;
    j["notes"] = r.notes;
    j["created_at"] = tpToJson(r.created_at);
    j["change_history"] = r.change_history;
}

inline void from_json(const nlohmann::json &j, Relationship &r) {
    r.id = j.at("id").get<RelationshipId>();
    r.from_id = j.at("from_id").get<PersonId>();
    r.to_id = j.at("to_id").get<PersonId>();
    r.type = j.at("type").get<RelationshipType>();
    r.type_label = j.at("type_label").get<std::optional<std::string> >();
    r.strength = j.at("strength").get<RelationshipStrength>();
    r.my_relationship_role = j.at("my_relationship_role").get<std::optional<std::string> >();
    r.is_active = j.at("is_active").get<bool>();
    r.threat_to_from = j.at("threat_to_from").get<ThreatInfo>();
    r.threat_to_me = j.at("threat_to_me").get<ThreatInfo>();
    r.metadata = j.at("metadata").get<RelationshipMetadata>();
    r.notes = j.at("notes").get<std::optional<std::string> >();
    r.created_at = tpFromJson(j.at("created_at"));
    r.change_history = j.at("change_history").get<std::vector<ChangeRecord> >();
}

// NOLINTEND(readability-identifier-length, *-pro-bounds-avoid-unchecked-container-access)
