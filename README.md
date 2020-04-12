# Create a Parallel World of Web Browser - From Chrome to Chromium for Application

## Internet Browsers have changed the world of software

Needless to say, Internet browsers have profoundly changed the world, and Google Chrome has set the de facto standard for browsers.

![1](/assets/1.png)

*(Internet browsers have created a way for people to change the content area of the browser through URLs, thereby enabling people to flexibly access Internet content.)*

Internet browsers have profoundly changed the way people get content, and also formed the separation between the Web and the Desktop.
When we specifically looked at the behavior of the browser software, we saw the basic facts reflected in the picture above. If we look at the software outside the browser, we see completely different scenarios. Other types of software lack the flexibility of the browser and the “getting content through the network”. It is difficult for people to imagine the following scenarios:

![2](/assets/2.png)

*(It is hard to imagine that an ordinary desktop application can access the URL like a browser to obtain the personalized software content that people expect and the flexibility that is comparable to a Web page.)*

Browsers give people a sense of inertia, which seems to make us overlook something. In fact, “web browsing” is the commonality of software.
If we open our brains further, it is even harder to imagine:

![3](/assets/3.png)

*(Web-based Office documents sound very ridiculous. In fact, there is a “shady screen” blocking the view. Once opened, a brand new software world will emerge …)*

When we turn our attention to ordinary application software, it will form a huge contrast with the characteristics of the browser: flexible and clumsy, rich content and functional limitations, network-based access and local loading constraints. Based on web pages, Internet browsers have created a rich web world with simple rules and a limited set of DOM elements. At this point, the field of desktop software is indeed dwarfed. These phenomena are a microcosm of the software industry today. Is there a reasonable solution to compensate for the deviation between the web browser and the application software system?

##Chromium for Application

Chromium for Application is a runtime architecture for Windows applications that enables developers to support all the functions of Chromium in their own application system. Its essence is to enable developers to reconstruct the main process (Browser process) of Chromium to fully utilize the double advantage of Win32 and Web. The purpose of Chromium for Application is to build a "bridge" between application software and Internet browsers, in order to make up for the lack of the Internet foundation of application software, to ensure that developers can construct application systems that conform to the characteristics of the modern Internet.
Let's look at a screenshot first:

![4](/assets/4.png)

This is a demonstration of an experimental Chromium version, which contains some elements not included in the official Chromium version:
1. Support Win32 elements;
2. Support Microsoft .NET Framework;
3. Additional native windows;
We can also provide further information, as shown below:

![5](/assets/5.png)

We see that components such as .NET, Win32, etc. that are blocked by the Chromium browser can completely return to Chromium. Google's strategy is to ensure the cleanliness of Web content, so Google has strict restrictions on Win32 within Chromium. This approach objectively ensures that the Chromium browser is relatively simple and secure, while also sacrificing the browser's programmable features. From the perspective of the developer, it limits the creativity of the developer, which is a great restriction on software productivity. Can we inherit the advantages of desktop and browser? If you can, then the browser model with the dual advantages of Chromium and Desktop can become a reality.

## Chromium GPU process, unlock the key to the puzzle

It all starts with dissecting the first Chromium browser window. What happens when we try to make some changes to Google Chromium? Let ’s take a look at the default new window of the standard Chromium browser. Consider this question: how to shrink and offset the display rectangle of the Web page to make room for other things? As shown below:

![6](/assets/6.png)

*(Can we modify the display rectangle of the Web page to make room inside the browser window?)*

Let's imagine that some "components" can be placed in the "grid", such as a .NET User Control, what will happen? When actually writing the code to achieve the scene described above, a shocking scene appeared, Chromium will "black out" everything you created, we saw the following scene:

![7](/assets/7.png)

*(Chromium will "black out" all the objects you create unless you follow its rules and work within the geometric area it stipulates)*

After countless experiments, we found that all Win32 objects were "blackened" by Chromium without exception. All of this has nothing to do with the main process of the browser. Every object is created normally, code interaction can be performed normally, and interoperation between components is completely normal, but it cannot be displayed normally. The initiator of all this is the Chromium GPU sub-process. This sub-process turns the Chromium browser into a "black hole". All objects created by other people are swallowed by this black hole. As a result, users can only see Google preset objects. Through this mode of sub-process division of labor, Google successfully excluded those mature technical frameworks, such as .NET, COM, Java, etc., from the browser running environment.
From a software design perspective, the GPU process does not enable the sandbox feature. All visible objects inside Chromium are drawn by the GPU process, and the responsibility of this process is very clear. We believe that the mechanism that excludes Win32 should not be based on Internet "security" considerations, but is a rule made deliberately by Google. Perhaps Google believes that the large and complex Win32 technical resources will impact the structure of the Chromium project, or perhaps it does not want to desktop application developers disrupted Chromium's software specifications. Therefore, the GPU process built a "separation wall" in this way. We cannot know the real reason. However, an objective fact is that this link greatly limits software productivity. The strategy of Chromium for Application is to "rationalize" the drawing work of GPU subprocesses, leaving room for an independent drawing for UI components of other technical frameworks. This consideration ensures that all Win32 objects can be rendered independently without affecting Chromium Its own drawing mechanism.

## Rearranging browser windows is a new starting point

It is an intuitive idea for the developer to rearranging the browser window. If it is feasible, then everything will become possible. Let ’s review the standard browser window:

![8](/assets/8.png)

The webpage monopolizes the client area, and it looks like there are no gaps or room.
If the geometric position of the web page display can be readjusted, the developer can re-layout the interior of the browser. Our assumption is that if it can be rearranged, then the layout should be descriptive and diverse. Breaking through the constraints of DOM is a new challenge facing Chromium for Application. With the development of the modern Internet, all kinds of developers can accept the expression and development standards of HTML pages. Chromium for Application expands the DOM elements according to the rules of the Web, and at the same time, it is very important to ensure that the Renderer is clean and safe. We believe that a rectangular area can basically accommodate two structures: 1. a grid structure; 2. a multi-layer structure. The multi-layer structure can be considered as a "1 row and n columns" grid, so in principle, there is only a grid structure, and the more complex layout within the rectangle is basically the nesting of the grid structure. We call the "1 row and 1 column" grid "node", then an m row and n column grid contain m * n node objects, and the grid can be nested recursively, so this structure can be written directly on the page in accordance with the XHTML standard. A node object can describe a Win32 object, Chromium for Application will create it in the main process, so it is reasonably isolated from the Renderer process. Win32 uses messages to communicate with Renderer. The Renderer can ignore messages. The interoperation between Win32 and Renderer is a "cross-process delegation". We provide developers with a "JavaScript Callback" processing solution. A request from the main process is converted into a JavaScript callback, which can provide enough "parameters" for the callback. Similar but different from .NET Delegate, the difference is that this delegation is cross-process, mainly to ensure that the Web cannot be "polluted" by Win32.
As shown in the figure, a grid structure of 4 rows and 3 columns:

![9](/assets/9.png)

Once the client area of the browser window can be rearranged, a new web page structure is specified. Since Chromium for Application includes all the functions of Chromium, the web page is the basic object of the application. If the web page has no substantial improvement, then Tolerating Chromium is meaningless. Taking full advantage of Web pages is a core topic. Once the application system is built on Chromium, things will fundamentally change. We have given two specific changes, the first: changes in the web page; the second: changes in JavaScript. The node element is added to the webpage. The simplest way to write a node is as follows:

```
<node nodetype="clrctrl" cnnid="TangramWinApp1.UserControl1,host"></node>
```

Here, "nodetype" marks the type of node, which can be "clrctrl", "activex", "splitter", etc. For details, please refer to our technical documentation. According to needs, a node can be a .NET Control, ActiveX, C ++ View, and various composite structures. The "cnnid" is the id of a specific object, depending on the implementation language. It enables developers to write more complex node grid structures. No details will be introduced here. Unlike the IE browser, the specific object corresponding to the node only provides a "structure description" on the page. The actual creation takes place in the Browser process to avoid polluting the "Web" Renderer process. The changes in JavaScript will be introduced in detail in subsequent articles.

## Create a "Parallel World" of the Chromium

We see that Chromium for Application enables the internal structure of a browser window to be "rearranged" with web pages. This step is an important starting point. From the perspective of the application window, the browser window is just one of many window types. In a broader sense, each window has an internal layout and is not much different from a browser window. What happens when we look at other windows with the idea of looking at browser windows? Let's take Excel as an example and look at the figure below:

![10](/assets/10.png)

Compare the above scenario with the previous scenario:

![11](/assets/11.png)

We found that everything that happened inside the web browser should be "reproduced" in Excel. What does that mean? Is there a completely identical channel (with the browser) showing clues?
Chromium for Application allows you to treat those application systems with completely different structures with consistent Web-based thinking. If we look at it from a geometric visual point of view, each window may be re-planned based on the "geometric layout" angle:

![12](/assets/12.png)

*(Looking for the "Parallel World" of the browser window, we are facing a completely different and colorful world ...)*

If you want a unified "page description" solution, then you need to solve several key questions. The first question is "What are the standards for page?". The second question is "Where is the page stored?". The third question is "How to parse the page to adapt to a different software?".
The first question: the standard of the page is still the web page. As a general solution, web pages have already existed in large numbers, and also cultivated the habits of users and developers. A basic starting point of Chromium for Application is to make more windows have Web characteristics. Once the application window meets certain conditions, then we can all treat it as a browser window, then they should all have "browsing behavior". That is to say, there is a type of webpage that adapts to the corresponding window, so the behavior of this type of window can be planned and controlled through the webpage. Because Chromium is open source and has huge community support, we have fully researched and compiled the Chromium project into a set of public software services. Unlike those browser controls, we have retained all the functions of chromium. Once Chromium becomes a public component, it has the "Runtime" feature, then other software can be connected to it in a consistent manner. Chromium becomes a runtime, which means that developers can access the "URL" for any purpose, and can obtain HTML pages in the same way as Chromium.
The second problem: the storage method of the page remains the same so that the most reasonable separation of application software functions can be realized, and the migration from the local to the server can make the software upgrade from a single software to a software service. The development model of the server has not changed.
The third question: We enable developers to display pages in a standard way. Of course, we also support the "sub-window" display mode. Chromium for Application gives developers more freedom and allows developers to use pages for their own purposes. In this case, some elements in the page may be different from the standard page. For example, it can be parsed as a WinForm, an Office document, a window with a special structure, etc., depending on the needs of the developer. That is to say, developers need to see any other elements as DOM, which requires a breakthrough in thinking. From a mathematical point of view, it is equivalent to expanding from "real numbers" to "complex numbers". We have given very "weak" conditions so that the vast majority of application windows can be given new software behaviors via the Web. Treating application software windows from a Web perspective is a great subversion of the concept of windows. In fact, once we look at other windows in the same way we look at browser windows, a software world that needs to be re-planned with Web ideas will become a reality.
As a result, we found that in the Internet mode, most software looks almost the same: you can describe specific application forms by organizing pages on the web backend, but the different pages assume different missions. The browser display page may be used to "see", the responsibility of HTML pages within other applications may be different depending on the application. It is possible that the page is not used to "see", but is used to determine application structures. Scripts may be used to control the behavior of application software.
The above ideas can be further expanded. We can adjust the Chromium Project to allow developers to do more things:
1. Allow developers to create their own Browser process;
2. Keep the Renderer process clean and tidy, allowing developers to extend the DOM according to Web rules;
3. Allow developers to use Win32 components reasonably within the Browser process;
4. Win32 is not allowed to interact directly with Renderer to ensure the integrity of the Chromium architecture;
Chromium's parallel world means that it has the same underlying mechanisms as Chromium for the Web. Each software parallel to Chromium can have its own principle of parsing pages, this aspect is different from Chromium. Parallel means that the structure is similar but completely different. In terms of supporting standard web pages, Chromium and the "parallel system" have a common foundation, and each Chromium for Application-based application will have its own object model. In addition to standard web pages, new pages composed of Win32 components (COM, .NET, Java ...) and standard DOM are also supported. With the support of Chromium for Application, each specific window may be a web page or a web page element, that is, the concept of the page has been extended, which is also an evolution of the standard page.

## Security is the limits of the Web

In the process of competition with IE, Chrome successfully positioned the criticism of Microsoft IE. In IE 6.0, each IE browser window runs in a separate thread, which contains various plug-ins based on COM and .NET. Because the COM, .NET code in the browser window and the script code in the web page are all running in the same thread, in particular, the Web DOM API of IE is implemented by COM technology, and the COM code in the thread can directly operate everything in the web page. Web content is completely exposed to the outside world, which brings great transparency to developers, and also brings great "security risks" to the Web. We believe that Google has discovered these problems before designing Chrome as a multi-process architecture. In the Chromium world, each page runs in a separate Renderer subprocess. Chrome uses the operating system sandbox to ensure that each Renderer subprocess cannot perform any GDI-related operations, cannot create window objects, and cannot operate the file system. Only limited APIs can be called. Renderer's responsibility is to parse the page and execute JavaScript scripts. In addition to these limited operations, it does nothing. From this perspective, Renderer is a safe and non-polluting environment. The Renderer child process is completely invisible to the user. What the user actually sees is the "geometric image" drawn by the GPU child process. Chromium internally converts a large number of elements used for browsers into "clean" JavaScript elements and DOM elements reflected on Web pages, allowing developers to safely interoperate software through scripts. The Renderer subprocess provides developers with a simple script running mode, which communicates with the outside world through IPC messages. This is a clear difference from Microsoft IE.
Needless to say, the emergence of Renderer is a revolution in terms of browser software structure. The only drawback is that this change is limited to the browser itself. If we choose where the biggest breakthrough in modern browsers is, we think the introduction of the Renderer process is an important breakthrough. Our idea is to retain all the features of Renderer completely so that the security of the Web will be guaranteed. With the help of IPC messages, Chromium for Application has taken a key step that was blocked by Chromium. This step is to allow Win32 components to talk to Renderer subprocesses in a cross-process manner. We allow a reasonable mapping relationship between Win32 objects and Renderer objects and clearly stipulate that Win32 does not allow direct manipulation and modification of Web content. This approach can ensure that Win32 and Web are available at the same time, giving developers maximum freedom. Chromium for Application enables Renderer to break the boundaries of browsers, allowing other application systems to have the ability to safely support Web pages.

## Jump out of browser window

We allow developers to refactor Chromium's main process (Browser process). This means that developers can choose their own familiar technical architecture to redesign the main process, giving developers maximum freedom. For example, developers can replace part of the browser window with their own window, and view the browser window as part of their application system, as shown below:

![13](/assets/13.png)

*(Refactoring the Browser process means that developers have greater autonomy)*

In fact, this concept allows Chromium Project to be used as a new starting point for applications. The strategy of Chromium for Application is to compile Chromium into a set of dynamic link libraries, so that developers can circumvent the complexity problems caused by Chromium Project, and at the same time avoid the user code "polluting" Chromium project itself. That is to say, users build their own engineering structures and solutions, and do not directly deal with the Chromium project. In this sense, Chromium for Application is a "code wall", ensuring the standardization and independence of the Chromium project. Since Chromium is open source, we can do it more thoroughly. The complete return of Win32 technology means that browser technology has broken through the limitations of browsers and entered the application field, which is very important.

## The Duty of Chromium for Application

The aim of Chromium for Application is that the core functions of the browser should be part of the public foundation of the software, not just the browser itself. From the perspective of technical architecture, no matter how Chrome and MSEdge will develop in the future, the essential difference between these two browsers and Chromium will not be too great. We believe that Chromium already contains more than 95% of Chrome and MSEdge's functions, individual differences and experience There must be an improvement, but Chromium for Application redefines the basic structure of the application software so that:
1. Windows-based application software can have the same multi-process architecture as Chromium. The main process of each application can have the complete functional structure of the Chromium Browser process. Software developers can use their familiar technical framework to develop the main process. Uses the Chromium browser window (including the browser sub-window), the main process supports all mainstream software runtimes, including Java, COM, .NET and C++;
2. Page as an application and each application can have its own web page with application characteristics;
3. Each application has a built-in modern browser;
4. Each application has its own web backend, which makes the software can be upgraded to a software service. The Renderer subprocess of each application is completely equivalent to the Chrome Renderer subprocess, and has the same sandbox mechanism;
5. IPC communication between Win32 and Renderer, and JavaScript callback mechanism;
6. The application system can have its own page interpretation behavior different from the standard browser;
Chromium for Application extends the concept of the browser to more general application systems and uses a Web-Desktop hybrid solution to break through the functional boundaries of the browser to adapt to the changes brought about by the Internet model.

## Application-oriented page system

Rearrangement means that the pages inside the browser window are "diversified", for example, developers can develop application-oriented Web pages:

![14](/assets/14.png)

*(Pages can be used to define your own functional units, and pages can effectively control the specific behavior of each function)*

Application pages are a kind of labeled application. Web pages control the operation logic of application objects. Many software behaviors can be migrated to the service backend. This organization is very conducive to the centralization of software functions. The application page can be embodied as a more general window:

![15](/assets/15.png)

*(Chromium for Application constructs the corresponding WinForm window by parsing the WinForm element in HTML)*

The specific functions of the application system can be embodied as a specific Web page. Once the application is organized based on pages, the functional organization of the application system is "website-ify".
Chromium for Application defines a "superset" of standard HTML pages, making the application system not only support standard HTML pages but also support a much larger set of "application pages". Each page is equivalent to a "sub-application" of the corresponding application. In fact, the structure of the application system redefined by Chromium for Application makes the application system upgrade from the core of "binary" elements to the core of the "application page".
Once your application system is connected to Chromium for Application, your application system will naturally become a web-based "ecosystem", and you can use huge Win32 components and standard DOM to synthesize pages of different forms to serve your users. Of course, you can make the page display different from the standard browser window, you can use your custom UI "shell". From the perspective of the page, each application has unlimited expansion possibilities. In fact, Chromium for Application not only compiles the Chromium project into a set of public software services but also turns mature frameworks such as .NET, Eclipse, etc. into public software services, which enables the application system to support the Web, .NET Framework and Java. This means that even if your application is a .NET or MFC program, you can also construct a browser window in your application and use the SWT window or Eclipse Workbench directly. All of these are pages, which can be handled uniformly with a unified Web mechanism, and thus completely change the structure of the application.

## Chromium for Application is an open project

Chromium.NET Wizard can be downloaded at https://marketplace.visualstudio.com/items?itemName=TangramDev.tangram-wizard
Chromium for Application includes open source and commercial parts. From an open and win-win perspective, we welcome friends from all walks of life to participate in this work, not limited to individuals, teams, companies, and investment cooperation.
