#include <cmath> 
#include <iostream> 

#include "TCanvas.h" 
#include "TF1.h" 
#include "TFile.h" 
#include "TFitResult.h" 
#include "TH1F.h" 
#include "TLegend.h" 
#include "TMath.h" 
#include "TMatrixD.h" 
#include "TROOT.h" 
#include "TRandom.h" 
#include "TStyle.h" 
#include "TGraphErrors.h"

void SetStyle(){
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

TGraphErrors* graph;
TCanvas* c1;

void fit(){
    graph = new TGraphErrors("Dati_germanio.txt", "%lg %lg");
    graph->SetTitle("Diodo al Germanio");
    c1 = new TCanvas("c1");
    
    graph->SetMarkerStyle(4);
    graph->Draw("AP");

    c1->SetLogy();
    c1->SetGrid();
    graph->GetXaxis()->SetTitle("Tensione (mV)");
    graph->GetYaxis()->SetTitle("Corrente (mA)");

    TF1 *f1 = new TF1("f1", "[0] * (exp(x/[1]) -1.)", 50, 250);
    f1->SetParameters(1e-6, 45.);
    f1->SetParName(0, "I_0");
    f1->SetParName(1, "Eta * V_T");
    
    graph->Fit("f1", "R");
    gStyle->SetOptFit(1111);
}