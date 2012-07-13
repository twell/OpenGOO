OpengooDebugSenderTool - OpenGooDst
======

The english version will be available soon!

 * [Introduzione](#introduzione)
 * [Compilazione](#compilazione)

### <a id="introduzione"></a>
##Introduzione 
OpenGooDst è un modulo di OpenGoo che permette di inviare al momento del crash del gioco un report formato dal backtrace + debug output e una breve descrizione dell'utente su quanto svolgeva al momento del crash.

OpenGooDst è separato da OpenGoo ed è formato da un wizard di invio report e un piccolo manager, in grado di visualizzare tutti i report, inviati e non inviati. E' inoltre possibile inviare dal manager eventuali report non inviati e di avere un [feedback di risoluzione](#feedback) di un particolare bug.

OpenGoo, al momento del crash, memorizza il backtrace e il debug output nel file [debug.xml](#debugFile), generando un identificatore univoco “Uuid” legato al report. Successivamente esegue OpenGooDst passandogli l'uuid come argomento.

Il modulo di OpenGoo che apre il file di debug.xml e memorizza il report è sul branch denominato: “XML-Module”. Non appena concluso sarà inglobato nel gioco.

OpenGooDst viene localizzato all'avvio con la lingua impostata nel gioco, tra quelle che saranno disponibili.

La determinazione del percorso al file di configurazione del gioco, come molte altre informazioni di architettura sono demandate al modulo che installerà OpenGoo nel sistema.

Vi è il problema di come raccogliere queste informazioni sulle diverse architetture su cui OpenGoo sarà distribuito.

###L'avvio:

All'avvio OpenGooDst valuta i parametri per determinare in che modalità avviarsi:

	-w -uuid=UUID_REPORT per wizard
	-m per manager

In avvio in modalità wizard, OpenGooDst apre il file debug.xml in cerca del report identificato dall'uuid passato come argomento, lo completa delle informazioni inserite dall'utente e lo invia.

### <a id="debugFile"></a>
###La struttura del file xml:


    <!DOCTYPE debugFile>
    <gameReports>

      <sysInfo os="*" architecture="*" build="*" gameVer="*" vga="*" driverVer="*" inUse="?">
    
          <report uuid="*" date-time="*" debugOutput="*" userDescription="*" sended="?" sendDate="*" fixed="?" gameVerFix="*"/>

    	 <report uuid=... />

               [...]

      </sysInfo>

      <sysInfo os="*"  ...

           <report uuid=...

      </sysInfo>

    </gameReports>

Gerarchicamente vi sono due nodi: L'architettura e il report.

L'Architettura: contiene tutte le informazioni strettamente architetturali, relative alla macchina su cui è installato i gioco e relative al gioco stesso (versione, num di build, vga, ecc.)

Il Report: è una singola segnalazione di un avvenuto bug, contenente tutte le informazioni a riguardo come il backtrace e il debug, la descrizione dell'utente, l'ora di avvenimento e informazioni di supporto.
Il report è legato gerarchicamente all'architettura che lo contiene.

Il file debug.xml viene popolato al momento del crash identificando l'architettura attualmente in uso. Quando il gioco viene aggiornato di versione, viene aggiunta una nuova architettura e i report verranno accodati a questa.

Prima di entrare nel dettaglio dei singoli campi del file debug.xml è bene precisare che un obbiettivo che vogliamo raggiungere è la possibilità di segnalare all'utente che quel bug segnalatoci è stato risolto, indicando inoltre con quale versione del gioco. A questo proposito alcuni campi sono progettati a supporto di [questa funzionalità](#feedback di risoluzione).

###I campi:

Architettura:
      
    <sysInfo os="*" arch="*" build="*" gameVer="120" vga="*" driverVer="*" inUse="true">

    </sysInfo>

 * os = sistema operativo in uso.
 * arch=id numerico dell'architettura.
 * build=numero di build del gioco.
 * gameVer=versione del gioco.
 * vga=modello di scheda video.
 * driverVer=versione del driver della scheda video.
 * inUse=flag che indica se l'architettura è quella attualmente in uso.

Report:

    <report uuid="*" date-time="*" debugOutput="**--#dump" userDescription="Has crashed!" sended="false" sendDate="*" fixed="true" gameVerFix="*"/>

 * uuid= identificativo univoco del report.
 * date-time= data/ora di avvenuto crash in UTC.
 * debugOutput= testo di backtrace + debug.
 * userDescription= descrizione a parole dell'utente.
 * sended = flag che indica se il report è stato inviato in rete.
 * sendDate = data/ora di invio in rete del report.
 * fixed= indica se il bug segnalato è stato risolto.
 * gameVerFix= indica la versione di gioco con cui è stato risolto il bug segnalato.

###Il report testuale:

Il formato del report inviato è generato da OpenGooDst, sulla base delle informazioni allocate, secondo il seguente formato:

    OpenGooDTS Report uuid generated on dateTime
    -----------------------------------------------------
    -                    Architecture                   -
    -----------------------------------------------------
    - GameVer in Build
    - Os on Arch with Vga, DriverVer
    -----------------------------------------------------
    -                     Report                        -
    -----------------------------------------------------
    -Tracer=
    DebugText
    -UserDescription=
    UserText
    -----------------------------------------------------
    Sended on sendDate

(Potrà subire sostanziali modifiche)

Il report verrà uplodato via ftp. Attualmente non abbiamo un server per lo scopo.

### <a id="feedback"></a>
###Feedback di risoluzione:
(Funzionalità attualmente non implementata)  
Il report viene generato ogni volta con un uuid univoco universalmente o con poche probabilità di duplicato.
Quando un bug viene risolto, viene aggiornato sul server un file xml contenente l'uuid del report + informazioni supplementari, come la versione del gioco con cui il bug è risolto.

All'avvio del manager, OpenGooDst scarica il file .xml cercando eventuali feedback.

Sorge il problema di gestire in modo efficiente i reports. È possibile quindi progettare un diverso tipo di file di segnalazione, raggruppabile con altri e con un formato più manipolabile.  

### <a id="compilazione"></a>
##Compilazione:

Per compilare sono necessarie le librerie qt.  
Svolgere i seguenti comandi.

 * qmake
 * make

Assicurarsi che il file dimostrativo test.xml sia nella cartella insieme all'eseguibile e che il programma venga eseguito con gli opportuni argomenti.


Initial Idea and Design:  
Fabrizio Signoretti - fasigno37@gmail.com  
Under GPLv3  
