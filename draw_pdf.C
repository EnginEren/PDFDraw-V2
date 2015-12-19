void draw_pdf() {
    
    void draw_Single(const char *total) {

        TCanvas *c1 = new TCanvas("c1","",200,10,700,500);
	    c1->DrawFrame(0,0,1,2.5);
	    c1->SetLogx();
	    ifstream ex;
	    ex.open(total);
	    const int n = 101;
	    Double_t x[n], y[n], ymax[n], ymin[n];
	    
        for(int i=0; i<n; i++){
		    double a,b,p,m;
		    ex >> a >> b >> p >> m;
            x[i]=a;  // x
		    y[i]=b;  // central y
		    ymax[i]=p;  // exp max y
            ymin[i]=m;  // exp min y
            
	    }    
	
	    gr = new TGraph(n,x,y);
	    gr->SetName("Center");
        grp = new TGraph(n,x,ymax);	
	    grp->SetName("Plus");
        grm = new TGraph(n,x,ymin);	
	    grm->SetName("Minus");
   	    grshade = new TGraph(2*n);
	    grshade->SetName("Shade");	
	    
        

        for (int j=0;j<n;j++) {
      	   grshade->SetPoint(j,x[j],ymax[j]);
      	   grshade->SetPoint(n+j,x[n-j-1],ymin[n-j-1]);
   	            
        }
	
        
        gr->SetTitle("");	
	    gr->SetLineWidth(1);
   	    gr->SetLineStyle(1);
	    gr->GetXaxis()->SetTitle("x");
	    grp->GetXaxis()->SetTitle("x");
	    gr->GetYaxis()->SetTitle("x.g(x,Q^{2})");
	    
        grshade->SetFillColor(kRed);
	    gr->Draw("AC");	
   	    grp->Draw("C");
   	    grm->Draw("C");
	    grshade->Draw("f");
        gr->Draw("SAME");	
    }
   
    void draw_Double (const char *first, const char *second, const char * relative, const char * relativeS, float ylimit, TString parton){
    
        //TCanvas *c3 = new TCanvas("c3","",200,10,700,500);
	    TCanvas *c3 = new TCanvas;
        //c3->DrawFrame(0,0,1,2.5);
	    //c3->SetLogx();
	    
        TPad *pad1 = new TPad("pad1","pad1",0,0.28,1,1);
        pad1->SetTopMargin(5);
        pad1->SetBottomMargin(0.001);
        pad1->Draw();
        pad1->SetLogx();
        pad1->cd();
        
        ifstream ex, mfile, rel, relS;
	    ex.open(first);
	    mfile.open(second);
        rel.open(relative);
        relS.open(relativeS);
	    const int n = 101;
	    Double_t x[n], y[n], ymax[n], ymin[n];
	    Double_t mymax[n], mymin[n];
	    Double_t relMax[n], relMin[n];
	    Double_t relMaxS[n], relMinS[n];
	    
        for(int i=0; i<n; i++){
		    double a,b,p,m, secondp, secondm;
            double arb1,arb2, arb3, arb4, arb5, arb6, relP, relM, relPS, relMS;
		    ex >> a >> b >> p >> m;
		    mfile >> arb1 >> arb2 >> secondp >> secondm;
            rel >> arb3 >> arb4 >> relP >> relM;
            relS >> arb5 >> arb6 >> relPS >> relMS;

            x[i]=a;  // x
		    y[i]=b;  // central y

		    ymax[i]=p;  // exp max y
            ymin[i]=m;  // exp min y
            
            mymax[i] = secondp;  //  max y for second
            mymin[i] = secondm;  // min y for second
		    
            relMax[i] = relP;   // max y for relative Uncert
            relMin[i] = relM;   // min y for relative Uncert
            
            relMaxS[i] = relPS;   // max y for relative Uncert
            relMinS[i] = relMS;   // min y for relative Uncert


	    }    
	
	    gr = new TGraph(n,x,y);
	    gr->SetName("Center");
        grp = new TGraph(n,x,ymax);	
	    grp->SetName("Plus");
        grm = new TGraph(n,x,ymin);	
	    grm->SetName("Minus");
   	    grshade = new TGraph(2*n);
	    grshade->SetName("Shade");	
	    
        
        grp_second = new TGraph(n,x,mymax);
        grm_second = new TGraph(n,x,mymin);
        grshade_second = new TGraph(2*n);
    
        grp_rel = new TGraph(n,x,relMax);
        grm_rel = new TGraph(n,x,relMin);
        grshade_rel = new TGraph(2*n);
        
        grp_relS = new TGraph(n,x,relMaxS);
        grm_relS = new TGraph(n,x,relMinS);
        grshade_relS = new TGraph(2*n);



        for (int j=0;j<n;j++) {
      		    grshade->SetPoint(j,x[j],ymax[j]);
      		    grshade->SetPoint(n+j,x[n-j-1],ymin[n-j-1]);
   	            
                grshade_second->SetPoint(j,x[j],mymax[j]);
      		    grshade_second->SetPoint(n+j,x[n-j-1],mymin[n-j-1]);
   	            
                grshade_rel->SetPoint(j,x[j],relMax[j]);
      		    grshade_rel->SetPoint(n+j,x[n-j-1],relMin[n-j-1]);
                
                grshade_relS->SetPoint(j,x[j],relMaxS[j]);
      		    grshade_relS->SetPoint(n+j,x[n-j-1],relMinS[n-j-1]);
   
        }
	
        
        gr->SetTitle("");	
	    gr->SetLineWidth(1);
   	    gr->SetLineStyle(1);
        TString fullpath = parton;
        parton += "(x,Q^{2})";
	    gr->GetYaxis()->SetTitle(parton);
	    
        gr->GetYaxis()->SetRangeUser(0.01,ylimit); 
        gr->GetYaxis()->SetTitleFont(2); 
        gr->GetXaxis()->SetRangeUser(0.0001,0.98); 
        grp->SetLineColor(kBlue);
	    grp->SetLineWidth(1);
        grm->SetLineColor(kBlue);
	    grm->SetLineWidth(1);
        
        grshade->SetFillColor(kGray+2);
        grshade->SetFillStyle(3004);
        grshade_second->SetFillColor(kAzure+10);
        
        gr->Draw("AC");	
        grshade_second->Draw("f");
	    grshade->Draw("SAMEf");
        grp->Draw("C");
   	    grm->Draw("C");
        TLegend *leg = new TLegend(0.1393678,0.7161017,0.5201149,0.8686441,NULL,"brNDC");
        leg->AddEntry(grshade,"HERA I+II DIS Exp. Uncert.","f");
        leg->AddEntry(grshade_second,"HERA I+II DIS + CMS Jets 8TeV Exp. Uncert.","f");
        leg->SetBorderSize(0);
        leg->SetFillColor(0);
        leg->Draw(); 
   
        TLatex *cms = new TLatex(0.0001,(ylimit * 1.04),"CMS NLO");
        TLatex *herapdf = new TLatex(0.04, (ylimit * 1.04) ,"HERAPDF Method (hessian)");
        cms->SetLineWidth(2);
        cms->Draw();
        herapdf->SetLineWidth(2);
        herapdf->Draw();

        pad1->Modified();
        pad1->Update();
        c3->cd();

        TPad *pad2 = new TPad("pad2","",0,0,1,0.28);
        //pad2->ResetAttPad();
        pad2->SetTitle("");;
        pad2->SetTopMargin(0.001);
        pad2->SetBottomMargin(0.34);
        pad2->Draw();
        pad2->cd();
        pad2->SetLogx();
       
        
        grp_rel->SetLineColor(kBlue);
	    grp_rel->SetLineWidth(1);
        grm_rel->SetLineColor(kBlue);
	    grm_rel->SetLineWidth(1);
        grshade_rel->SetTitle("");
        grshade_relS->SetTitle("");
        grshade_relS->GetXaxis()->SetLabelSize(0.1); 
        grshade_relS->GetXaxis()->SetTitle("x"); 
        grshade_relS->GetXaxis()->SetTitleSize(0.12); 
        grshade_relS->GetXaxis()->SetTitleOffset(1); 
        
        grshade_relS->GetYaxis()->SetTitle("Fract. Uncertainty"); 
        grshade_relS->GetYaxis()->SetLabelSize(0.07); 
        grshade_relS->GetYaxis()->SetTitleFont(2); 
        grshade_relS->GetYaxis()->SetTitleOffset(0.34); 
        grshade_relS->GetYaxis()->SetTitleSize(0.09); 
        grshade_rel->GetYaxis()->SetRangeUser(-0.49,0.49); 
        grshade_relS->GetYaxis()->SetRangeUser(-0.49,0.49); 
        grshade_rel->GetXaxis()->SetRangeUser(0.0001,0.98); 
        grshade_relS->GetXaxis()->SetRangeUser(0.0001,0.98); 
        grshade_rel->SetFillColor(kGray+2);
        grshade_rel->SetFillStyle(3004);
        grshade_relS->SetFillColor(kAzure+10);
        
        grshade_relS->Draw("Af");
        grshade_rel->Draw("SAMEf");
        
        grp_rel->Draw("C");
        grm_rel->Draw("C");

        
        pad2->Modified();
        pad2->Update();
        c3->Update();    
    }
    
    
    
    
    void draw_bandsBR(const char *exp , const char *model, const char *param) {
        TCanvas *c2 = new TCanvas("c2","",200,10,700,500);
	    c2->DrawFrame(0,0,1,2.5);
	    c2->SetLogx();
	    ifstream ex, mfile, pfile;
	    ex.open(exp);
	    mfile.open(model);
	    pfile.open(param);
	    const int n = 101;
	    //TFile *f = new TFile("plots.root","recreate");
	    Double_t x[n], y[n], ymax[n], ymin[n];
	    Double_t mymax[n], mymin[n];
	    Double_t pymax[n], pymin[n];
	    
        for(int i=0; i<n; i++){
		    double a,b,p,m, modelp,modelm, paramp, paramm;
		    ex >> a >> b >> p >> m;
		    mfile >> modelp >> modelm;
		    pfile >> paramp >> paramm;
		    
            x[i]=a;  // x
		    y[i]=b;  // central y
		    ymax[i]=p;  // exp max y
            ymin[i]=m;  // exp min y
            
            mymax[i] = modelp;  // model max y
            mymin[i] = modelm;  // model min y
		    
            pymax[i] = paramp; // param max y
            pymin[i] = paramm; // param min y

	    }    
	
	    gr = new TGraph(n,x,y);
	    gr->SetName("Center");
        grp = new TGraph(n,x,ymax);	
	    grp->SetName("Plus");
        grm = new TGraph(n,x,ymin);	
	    grm->SetName("Minus");
   	    grshade = new TGraph(2*n);
	    grshade->SetName("Shade");	
	    
        
        grp_model = new TGraph(n,x,mymax);
        grm_model = new TGraph(n,x,mymin);
        grshade_model = new TGraph(2*n);
    
        grp_param = new TGraph(n,x,pymax);
        grm_param = new TGraph(n,x,pymin);
        grshade_param = new TGraph(2*n);


        for (int j=0;j<n;j++) {
      		    grshade->SetPoint(j,x[j],ymax[j]);
      		    grshade->SetPoint(n+j,x[n-j-1],ymin[n-j-1]);
   	            
                grshade_model->SetPoint(j,x[j],mymax[j]);
      		    grshade_model->SetPoint(n+j,x[n-j-1],mymin[n-j-1]);
   	    
                grshade_param->SetPoint(j,x[j],pymax[j]);
      		    grshade_param->SetPoint(n+j,x[n-j-1],pymin[n-j-1]);

        }
	
        
        gr->SetTitle("");	
	    gr->SetLineWidth(1);
   	    gr->SetLineStyle(1);
	    gr->GetXaxis()->SetTitle("x");
	    grp->GetXaxis()->SetTitle("x");
	    gr->GetYaxis()->SetTitle("x.u_{v}(x,Q^{2})");
	    
        grshade->SetFillColor(kRed);
        grshade_model->SetFillColor(kYellow);
        grshade_param->SetFillColor(kGreen);
	    gr->Draw("AC");	
   	    grp->Draw("C");
   	    grm->Draw("C");
	    grshade->Draw("f");
	    
        grp_model->Draw("C");
   	    grm_model->Draw("C");
	    grshade_model->Draw("SAMEf");

        grp_param->Draw("C");
   	    grm_param->Draw("C");
	    grshade_param->Draw("SAMEf");

        
        
        gr->Draw("SAME");	
    }	

    //draw_bandsBR("g.txt", "g-model.txt", "g-para.txt");
    //draw_Single("store/gluon-EXP-hera");
  
    draw_Double("store/gluon-EXP-hera","store/gluon-EXP-hera+cms", "store/gluon-EXP-relative-hera", "store/gluon-EXP-relative-hera+cms",4,"x #bullet g");
    draw_Double("store/up-EXP-hera","store/up-EXP-hera+cms", "store/up-EXP-relative-hera", "store/up-EXP-relative-hera+cms",1,"x #bullet u_{v}");
    draw_Double("store/down-EXP-hera","store/down-EXP-hera+cms", "store/down-EXP-relative-hera", "store/down-EXP-relative-hera+cms",0.6,"x #bullet d_{v}");


}
