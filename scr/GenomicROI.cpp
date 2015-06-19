//
//  GenomicROI.cpp
//  ExtractGenomicROI
//
//  Created by Manuel Tuschen on 24.11.14.
//  Copyright (c) 2014 Manuel Tuschen. All rights reserved.
//

#include "GenomicROI.h"


GenomicROI::GenomicROI(){
  this->_restrictions = new std::map<std::string, std::set<std::string>>();
  this->_hasRestrictions = false;
    
}


GenomicROI::~GenomicROI() {
  delete _restrictions;
  _restrictions = nullptr;
}


void GenomicROI::setRestrictionsFromMap(std::map<std::string, std::set<std::string>> const & restrictions) {
    *this->_restrictions = restrictions;
    this->_hasRestrictions = true;
}


void GenomicROI::setRestrictionsFromCsv(std::list<fs::CsvFormat<std::string>> const & restrictions) {
  
    // got through the csv list
    for (auto it = restrictions.cbegin(); it != restrictions.cend(); ++it) {
        std::list<std::string> line = it->aline();
        
        // grap the first element as key
        std::string key = line.front();
        line.pop_front();
      
      
        // create set with all remaining values
        std::set<std::string> values;
        for (auto jt = line.cbegin(); jt != line.cend(); ++jt) {
          values.emplace(*jt);
        }
        this->addRestrictions(key, values);
    }
  
  this->_hasRestrictions = true;
}


void GenomicROI::addRestrictions(std::string const & key, std::set<std::string> const & values) {
 
  if (this->_restrictions->find(key) != this->_restrictions->cend()) {
    
    // all values needed to be added
    for (auto it = values.cbegin(); it != values.cend(); ++it) {
      this->_restrictions->find(key)->second.emplace(*it);
    }
  } else {
    
    // a new elements needed to be constructed
    this->_restrictions->emplace(key, values);
  }
  
  this->_hasRestrictions = true;
}


void GenomicROI::addRestriction(std::string const & key, std::string const& value) {
    
  if (this->_restrictions->find(key) != this->_restrictions->cend()) {
      this->_restrictions->find(key)->second.emplace(value);
  } else {
    
    std::set<std::string> value_to_inser = {value};
    this->_restrictions->emplace(key, value_to_inser);
  }
  
  this->_hasRestrictions = true;
}


void GenomicROI::deleteRestrictions(std::string const & key) {
  
  this->_restrictions->erase(key);
  
  if (this->_restrictions->empty() == true) {
    this->_hasRestrictions = false;
  }
}


void GenomicROI::deleteRestriction(std::string const & key , std::string const & values) {
  
  auto key_it = this->_restrictions->find(key);
  if (key_it != this->_restrictions->cend()){
      
    // find the value to delete in the vector
    key_it->second.erase(values);
  }
  
  if (key_it->second.empty() == true) {
    this->_restrictions->erase(key);
  }
  
  if (this->_restrictions->empty() == true) {
    this->_hasRestrictions = false;
  }
}


std::map<std::string, std::set<std::string>> const & GenomicROI::restrictions() const {
    return *this->_restrictions;
}



std::set<std::string> const & GenomicROI::getRestrictionsFromKey(std::string const & key) const {
    return this->_restrictions->find(key)->second;
}



void GenomicROI::extractROI(std::list<fs::GffFormat>& genomicRegions) {
  
  // sort genomic regions first
  genomicRegions.sort();
  
  // create a vector with all possible members of a gff object not belonging to
  // the attribute
  
  // go through all the gff objects
  for (auto it = genomicRegions.cbegin(); it != genomicRegions.cend(); ++it) {
      
    // for each member of the object check if it is restricted in any form
    // if a restriction does not match, the object is deleted.
     
    // check if there is a restriction for seqname
    auto jt = this->_restrictions->find("seqname");

    if ( jt != this->_restrictions->end()) {
      std::string itemToCheck = it->seqname();

      // if the item found is not in the restriction list delete this gff
      // object from the list later
      if (jt->second.count(itemToCheck) == 0) {
        it = genomicRegions.erase(it);
        it--;
        continue;
      }
    }
      
    // check if there is a restriction for source
    jt = this->_restrictions->find("source");
    
    if ( jt != this->_restrictions->end()) {
      std::string itemToCheck = it->source();
      // if the item found is not in the restriction list delete this gff
      // object from the list later
      if (jt->second.count(itemToCheck) == 0) {
        it = genomicRegions.erase(it);
        it--;
        continue;
      }
    }
      
    // check if there is a restriction for feature
    jt = this->_restrictions->find("feature");
      
    if ( jt != this->_restrictions->end()) {
      std::string itemToCheck = it->feature();
      // if the item found is not in the restriction list delete this gff
      // object from the list later
      if (jt->second.count(itemToCheck) == 0) {
        it = genomicRegions.erase(it);
        it--;
        continue;
      }
    }
    
    
    if (it->hasAttribute_map() == true) {
        
    //now check all the attributes
    for ( auto jt = this->_restrictions->cbegin(); jt != this->_restrictions->cend(); ++jt) {
      
      // see if there is such an attribute in the map
      if (it->attribute_map().find(jt->first) != it->attribute_map().cend()) {
        std::string itemToCheck = it->attribute_map().find(jt->first)->second;
          if (jt->second.count(itemToCheck) == 0) {
            it = genomicRegions.erase(it);
            it--;
            break;
          }
        }
      }
    }
  }
}


