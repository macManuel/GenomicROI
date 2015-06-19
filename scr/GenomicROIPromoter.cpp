//
//  GenomicROIPromoter.cpp
//  ExtractGenomicROI
//
//  Created by Manuel Tuschen on 24.11.14.
//  Copyright (c) 2014 Manuel Tuschen. All rights reserved.
//

#include "GenomicROIPromoter.h"

/**
 *  The constructor.
 *
 *  @param genomicRegions All genomic regions.
 *
 */
GenomicROIPromoter::GenomicROIPromoter(int lengthUpstreamTSS, int lengthDownstreamTSS) {
  
  this->_lengthUpstreamTSS = std::abs(lengthUpstreamTSS);
  this->_lengthDownstreamTSS = std::abs(lengthDownstreamTSS);
}


GenomicROIPromoter::~GenomicROIPromoter() {
  
}


int GenomicROIPromoter::lengthUpstreamTSS() const {
  return this->_lengthUpstreamTSS;
}


int GenomicROIPromoter::lengthDownstreamTSS() const {
  return this->_lengthDownstreamTSS;
}


void GenomicROIPromoter::setLengthUpstreamTSS(int lengthUpstreamTSS) {
  this->_lengthUpstreamTSS = std::abs(lengthUpstreamTSS);
}


void GenomicROIPromoter::setLengthDownstreamTSS(int lengthDownstreamTSS) {
  this->_lengthDownstreamTSS = std::abs(lengthDownstreamTSS);
}



void GenomicROIPromoter::setPromotor(std::list<fs::GffFormat>& genomicRegions) {
    
  // go through the genomicRegions to considere
  for (auto it = genomicRegions.begin(); it != genomicRegions.end(); ++it) {
    
    // get the strand to look for the starting point
    // if no strand is set, + is assumed
    char strand = '+';
    if (it->strand() == '-') {
        strand = '-';
    }
        
    //calculate the start and end point of the region of the new promoter
        
    // for a positive strand 'start' is the TSS
    if (strand == '+') {
        unsigned int tmp = it->start();
        it->setStart(tmp - lengthUpstreamTSS());
        it->setEnd(tmp + lengthDownstreamTSS());
            
    // for a negative strand 'end' is the TSS
    } else {
      unsigned int tmp = it->end();
      it->setEnd(tmp + lengthUpstreamTSS());
      it->setStart(tmp - lengthDownstreamTSS());
    }
      
    // last, mark the region as promoter
    
    if (it->hasAttribute_string() == true) {
      std::string tmp = it->attribute_string();
      it->setAttribute_string(tmp + "; gene_region \"promoter\"");
    } else {
      it->addAttribute("gene_region", "promoter");
    }
  }
}


