//
//  GenomicROIPromotor.h
//  EpigeneticScoring
//
//  Created by Manuel Tuschen on 13.11.14.
//  Copyright (c) 2014 Manuel Tuschen. All rights reserved.
//

#ifndef EpigeneticScoring_GenomicROIPromotor_h
#define EpigeneticScoring_GenomicROIPromotor_h

#include <stdlib.h>

#include "GenomicROI.h"


    /**
     *  Subclass of GenomicROI to set the given genomic region to a promoter of
     *  a given size.
     */
  class GenomicROIPromoter : public GenomicROI {
    
  protected:
    /**
     *  The number of bases upstream of TSS.
     */
    int _lengthUpstreamTSS;
    
    /**
     *  The number of bases downstream of TSS.
     */
    int _lengthDownstreamTSS;
    
    
  
    public:
    /**
     *  The constructor.
     */
    GenomicROIPromoter(int lengthUpstreamTSS, int lengthDownstreamTSS);
    
    /**
     *  The destructor
     */
    virtual ~GenomicROIPromoter();
    
    /**
     *  Get the number of bases upstream of TSS.
     *
     *  @return the number of bases upstream of TSS.
     */
    int lengthUpstreamTSS() const;
    
    /**
     *  Get the number of bases downstream of TSS.
     *
     *  @return the number of bases downstream of TSS.
     */
    int lengthDownstreamTSS() const;
    
    /**
     *  Set the number of bases downstream of TSS.
     *
     *  @param lengthUpstreamTSS An unsigned int of the length.
     */
    void setLengthUpstreamTSS(int lengthUpstreamTSS);
    
    /**
     *  Set the number of bases downstream of TSS.
     *
     *  @param lengthUpstreamTSS An unsigned int of the length.
     */
    void setLengthDownstreamTSS(int lengthDownstreamTSS);
    
    
    /**
     *  he function to set each element of gff list to a promoter size
     *
     *  @param genomicRegions A gff list which will be modified.
     */
    void setPromotor(std::list<fs::GffFormat>& genomicRegions);
        
    
    };
#endif
