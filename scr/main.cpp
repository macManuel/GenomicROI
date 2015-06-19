//
//  main.cpp
//  ExtractGenomicROI
//
//  Created by Manuel Tuschen on 13.11.14.
//  Copyright (c) 2014 Manuel Tuschen. All rights reserved.
//

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

#include <fs_clap.h>
#include <fs_formats.h>
#include <fs_io.h>

#include "GenomicROI.h"
#include "GenomicROIPromoter.h"

// This programm is designed to extract promoter regione out of a .gff, .gtf or .gff3 file. The extracted genomic regions are stored in the same directory as ther original file.
//
//
// Parameters:
// # --input <filename>:  A .gff file (version 1-3) including the path with those genomic regrions to extract from.
// # --restrictions <filename>: A ';' separated .csv file including the path. Each line must start with a gff field item or attribute  item. If a gff line does not match any of the following values for tht specific entry, this line will not be considered. Only string items are considered at the moment!
// # --promoter <-bp +bp>: If this flag is set the start and stop values are set for the promoter size. -bp and +bp reflect the start and end position of the promoter relative to the TSS


int main(int argc, const char * argv[]) {
  
  // First set up all the command line arguments to be parsed
  fs::CommandlineParser myParser("1.0", "Extract the promotor regions.");
  
  fs::ClapSingleArgument<std::string> fileArgument(myParser, "input", "<filename>", "A .gff file (version 1-3) including the path with those genomic regrions to extract from.");
  fs::ClapSingleArgument<std::string> restrictionArgument(myParser, "restrictions", "<filename>", "A ';' separated .csv file including the path. Each line must start with a gff field item or attribute  item. If a gff line does not match any of the following values for that specific entry, this line will not be considered. Only string items are considered at the moment!", false);
  fs::ClapMultiArgument<int> promoterArgument(myParser, "promoter", "<bp bp>", "If this flag is set the start and stop values are set for the promoter size. bp and bp reflect the start (upstream) and end (downstream) position of the promoter relative to the TSS.", false);
  
  // Now perform the parsing and extract the values
  myParser.parse(argc, argv);
  
  // As we now have everything, the program may start its computations
  
  // We need a list to store our gff objects in:
  //std::list<fs::GffFormat>* gff_list = new std::list<fs::GffFormat>;
  std::list<fs::GffFormat> gff_list;

  // Read in the gff file:
  fs::GffReader gff_input(fileArgument.value());
  gff_input.readFromFile(gff_list);
  
  // Next we need the restrictions if they were given
  std::list<fs::CsvFormat<std::string>> restriction_list;
  if (restrictionArgument.isSet() == true) {
    fs::CsvReader<std::string> csv_input(restrictionArgument.value());
    csv_input.readFromFile(restriction_list);
  }
  
  // Do we need to set promoters or just extract the values of interest?
  if (promoterArgument.isSet() == true) {
    // perform extraction of region of interest using the correct file type and parameters
    GenomicROIPromoter roi(promoterArgument.value().at(0), promoterArgument.value().at(1));
    
    if (restrictionArgument.isSet() == true) {
      roi.setRestrictionsFromCsv(restriction_list);
      
    }
    roi.extractROI(gff_list);
    roi.setPromotor(gff_list);
  } else {
    GenomicROI roi;
    if (restrictionArgument.isSet() == true) {
      roi.setRestrictionsFromCsv(restriction_list);
    }
  }
  
  // finally write the output file
  fs::GffWriter gff_output(gff_input.path() + gff_input.file() + "_roi" + gff_input.suffix(),3);
  gff_output.writeIntoFile(gff_list);
  std::cout << "Finished!" << std::endl;
  
  return 0;
}
