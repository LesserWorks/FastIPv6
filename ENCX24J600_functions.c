extern uint16_t ReadPHY(uint8_t PHYaddress)
{
  indir(MIREGADRL) = PHYaddress;
  indir(MIREGADRH) = 1U;
  indir(MICMDL) = 1 << MIIRD;
  indir(MICMDH) = 0; // Can this line be deleted?
  while(indir(MISTATL) & (1 << BUSY));
  indir(MICMDL) = 0;
  indir(MICMDH) = 0;
  return (((uint16_t)indir(MIIRDH)) << 8) | (indir(MIIRDL);
                                             }
                                             
                                          
                                    
                                             
