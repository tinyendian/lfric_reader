/*
 * @class   vtkNetCDFLFRicReader
 * @brief   Read netCDF files with LFRic output in ugrid format.
 *
 * Reads in a netCDF file with LFRic output in ugrid format and
 * produces an unstructured grid. The grid is unstructured in
 * horizontal dimension and extruded in the vertical.
*/

#ifndef vtkNetCDFLFRicReader_h
#define vtkNetCDFLFRicReader_h

#include <vtkIONetCDFModule.h> // For export macro
#include <vtkUnstructuredGridAlgorithm.h>
#include <vtkUnstructuredGrid.h>
#include <vtk_netcdf.h>

#include <vector>

// Set automatically with PV plugin debug?
#define DEBUG 1

class VTKIONETCDF_EXPORT vtkNetCDFLFRicReader : public vtkUnstructuredGridAlgorithm {
public:
  vtkTypeMacro(vtkNetCDFLFRicReader,vtkUnstructuredGridAlgorithm);
  static vtkNetCDFLFRicReader *New();
  void PrintSelf(ostream& os, vtkIndent indent) override;

  // Specify name of input data file
  vtkSetStringMacro(FileName); // Defines SetFileName()
  vtkGetStringMacro(FileName); // Defines GetFileName()

protected:

  vtkNetCDFLFRicReader();
  ~vtkNetCDFLFRicReader() override;

  // Return time steps from the input file
  int RequestInformation(vtkInformation*, vtkInformationVector**,
                         vtkInformationVector*) override;

  // Return grid and field data from the input file
  int RequestData(vtkInformation *, vtkInformationVector **,
                  vtkInformationVector *) override;

  // Build VTK grid from UGRID description
  int CreateVTKGrid(const int ncid, vtkUnstructuredGrid *grid);

  // Read field data from netCDF file and add to the VTK grid
  int LoadFields(const int ncid, vtkUnstructuredGrid *grid);

  // Utility functions
  size_t getNCDim(const int ncid, const char * dimname);

  std::vector<double> getNCVarDouble(const int ncid, const char * varname, const std::initializer_list<size_t> start, const std::initializer_list<size_t> count);
  std::vector<unsigned long long> getNCVarULongLong(const int ncid, const char * varname, const std::initializer_list<size_t> start, const std::initializer_list<size_t> count);

  char *FileName;

private:

  vtkNetCDFLFRicReader(const vtkNetCDFLFRicReader&) = delete;
  void operator=(const vtkNetCDFLFRicReader&) = delete;

  double * TimeSteps;
  size_t NumberOfTimeSteps, NumberOfLevels, NumberOfFaces2D;

};
#endif
