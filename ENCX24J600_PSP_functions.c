extern uint16_t ReadPHY(const uint8_t PHYaddress)
{
  while(indir(MISTATL) & (1 << BUSY)); // Wait for previous operation to finish
  indir(MIREGADRL) = PHYaddress; // Load address
  indir(MIREGADRH) = 1U;
  indir(MICMDL) = 1 << MIIRD; // Start read
  indir(MICMDH) = 0; // Can this line be deleted?
  while(indir(MISTATL) & (1 << BUSY)); // Wait for read to finish
  indir(MICMDL) = 0; // Clear MIIRD
  indir(MICMDH) = 0;
  return (((uint16_t)indir(MIRDH)) << 8) | indir(MIRDL); // Read result
}

extern void WritePHY(const uint8_t PHYaddress, const uint8_t PHYdatahigh, const uint8_t PHYdatalow)
{
  while(indir(MISTATL) & (1 << BUSY)); // Wait for previous operation to finish
  indir(MIREGADRL) = PHYaddress; // Load address
  indir(MIREGADRH) = 1U;
  indir(MIWRL) = PHYdatalow; // Load data
  indir(MIWRH) = PHYdatahigh; // Load data, automatically starts write operation
  return;
}

extern void startPHYscan(const uint8_t PHYaddress)
{
  while(indir(MISTATL) & (1 << BUSY)); // Wait for previous operation to finish
  indir(MIREGADRL) = PHYaddress; // Load address
  indir(MIREGADRH) = 1U;
  indir(MICMDL) = 1 << MIISCAN; // Start read
  indir(MICMDH) = 0; // Can this line be deleted?
  while(indir(MISTATL) & (1 << NVALID)); // Wait for first valid data
  return;
}

extern uint16_t readPHYscan(void)
{
  return (((uint16_t)indir(MIRDH)) << 8) | indir(MIRDL); // Read registers
}

extern void stopPHYscan(void)
{
  indir(MICMDL) = 0; // Clear MIISCAN
  indir(MICMDH) = 0; // Can this line be deleted?
  return;
}
                                          
                                    
                                             
