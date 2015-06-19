//
//  GenomicROI.h
//  EpigeneticScoring
//
//  Created by Manuel Tuschen on 13.11.14.
//  Copyright (c) 2014 Manuel Tuschen. All rights reserved.
//

#ifndef EpigeneticScoring_GenomicROI_h
#define EpigeneticScoring_GenomicROI_h

#include <map>
#include <set>
#include <list>
#include <string>

#include <fs_formats.h>

/**
 *  This is a base class to extract the genomics regions of interest in a given
 *  list of gffFormnat objects. Be aware, that the original list is being modified
 *  when using this class !
 */
class GenomicROI {

protected:
  /**
   *  A map containg all the restrictions. Each entry in the gffFormat list 
   *  which does not match these restrictions will be deleted.
   */
  std::map<std::string, std::set<std::string>>* _restrictions;
  
  /**
   *  A boolean indicating if there are any restrictions given.
   */
  bool _hasRestrictions;
  
public:
  
  /**
   *  A standard constructor for this class.
   */
  GenomicROI();
  
  /**
   *  The destructor.
   */
  virtual ~GenomicROI();
  
  
  /**
   *  Set the restrictions by using a map with keys indicating a gff feature
   *  and values representing the features values.
   *
   *  @param restrictions A map with two strings.
   */
  void setRestrictionsFromMap(std::map<std::string, std::set<std::string>> const & restrictions);
  
  /**
   *  Set the restricitons directly with entrys from a .csv file.
   *
   *  @param restrictions A list of lines extraced from a .csv file.
   */
  void setRestrictionsFromCsv(std::list<fs::CsvFormat<std::string>> const & restrictions);
  
  /**
   *  Add one type of restrictions includingi ts values.
   *
   *  @param key    The key describing the a gff attribute.
   *  @param values A set of values for that key.
   */
  void addRestrictions(std::string const & key , std::set<std::string> const & values);
  
  /**
   *  Add one restriction value for a specific key.
   *
   *  @param key    The key describing the a gff attribute.
   *  @param value One restriction.
   */
  void addRestriction(std::string const & key , std::string const & value);
  
  /**
   *  Delete all restriciotns of a specific key.
   *
   *  @param key The type or attribute.
   */
  void deleteRestrictions(std::string const & key);
  
  /**
   *  Delete one restriciotns of a specific key.
   *
   *  @param key    The key describing the a gff attribute.
   *  @param values One restriction to delete.
   */
  void deleteRestriction(std::string const & key , std::string const & values);
  
  
  /**
   *  Returns all restricitons for reading purposes only.
   *
   *  @return The restricitons.
   */
  std::map<std::string, std::set<std::string>> const &  restrictions() const;
  
  /**
   *  Retrun all restictions fo one key.
   *
   *  @param key TThe key describing the a gff attribute.
   *
   *  @return The restrictions.
   */
  std::set<std::string> const & getRestrictionsFromKey(std::string const & key) const;
  
  
  /**
   *  The functions extraction the regions of interest.
   *
   *  @param genomicRegions A list wit gff objects which will be modified !.
   */
  void extractROI(std::list<fs::GffFormat>& genomicRegions);
  
  
};

#endif
