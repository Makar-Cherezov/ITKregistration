#include "utils.h"


std::vector<std::string> GetFilesInDir(std::filesystem::path directoryPath)
{
  std::vector<std::string> fileNames;
  for (const auto & entry :
       std::filesystem::directory_iterator(directoryPath))
  {
    if (std::filesystem::is_regular_file(entry) &&
        (entry.path().extension() == ".tif" ||
         entry.path().extension() == ".tiff"))
    {
      fileNames.push_back(entry.path().string());
    }
  }
  return fileNames;
}

void fillFileNames(std::vector<std::string>* srcFileNames, std::vector<std::string>* refFileNames, Ui::MainWindow* ui)
{
        QDir srcDir, refDir;
        srcDir = QFileInfo(ui->srcPathLabel->text()).absoluteFilePath();
        srcDir.setFilter(QDir::Files | QDir::Readable);
        refDir = QFileInfo(ui->refPathLabel->text()).absoluteFilePath();
        refDir.setFilter(QDir::Files | QDir::Readable);
        for ( QString str : srcDir.entryList()) {
          srcFileNames->push_back(srcDir.path().toStdString() + '/' + str.toStdString());
        }
        for ( QString str : refDir.entryList()) {
          refFileNames->push_back(refDir.path().toStdString() + '/' + str.toStdString());
        }
}

void PrintSlice(itk::Image<float, 3>::Pointer fixedImage)
{
    using ImType = itk::Image<float, 3>;
    std::cout << "Printing" << std::endl;
    itk::NeighborhoodIterator <ImType>::RadiusType radius;
    radius.Fill(1);
    itk::NeighborhoodIterator <ImType> it( radius, fixedImage, fixedImage->GetRequestedRegion());
    itk::NeighborhoodIterator <ImType>::OffsetType offset = { { -1, -1 } };
    for (it.GoToBegin(); !it.IsAtEnd(); ++it){
        if (it.GetPixel(offset) > 0)
        {
        std::cout << it.GetPixel(offset) << " | ";
        return;
        }
    }

//    for (int i = 120; i <= 190; ++i)
//    {
//        for (int j = 120; j <= 190; ++j)
//        {
//            for (int k = 120; k <= 190; ++k)
//            {
//                const itk::Image<float, 3>::IndexType index = {
//                { i, j, k }
//                };

//                pixelFile << fixedImage->GetPixel(index) << ' ';


//                std::cout << "pixel written" << std::endl;
//            }
//            pixelFile << std::endl;
//        }
//        pixelFile << std::endl;
//    }
}
